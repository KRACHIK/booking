
#include "logic_impl.h"

namespace Java {

	CProperties::CProperties() {}

	CProperties::CProperties(
		int startDay
		, int  startMonth
		, int  startYear
		, int  endDay
		, int  endMonth
		, int  endYear
		, const std::string & outputDirectory
	) : _startDay(startDay)
		, _startMonth(startMonth)
		, _startYear(startYear)
		, _endDay(endDay)
		, _endMonth(endMonth)
		, _endYear(endYear)
		, _outputDirectory(outputDirectory)
	{
	}


	void CProperties::CreateProperties(std::string sFileName)
	{
		std::stringstream ss;

		ss << "startDay=" << _startDay << "\n";
		ss << "startMonth=" << _startMonth << "\n";
		ss << "startYear=" << _startYear << "\n";
		ss << "endDay=" << _endDay << "\n";
		ss << "endMonth=" << _endMonth << "\n";
		ss << "endYear=" << _endYear << "\n";
		ss << "outputDirectory=" << _outputDirectory << "\n";

		std::ofstream outFile(sFileName);
		outFile << ss.rdbuf();
		outFile.close();
	}
}


namespace client
{
	CTask::CTask()
	{
	}

	CTask::CTask(Java::CProperties Properties
		, const std::string & sFullPath,
		const std::string  & sDirProp
	)
		: _Properties(Properties)
		, _sFullPath(sFullPath)
		, _sDirProp(sDirProp)
	{

	}

	std::string CTask::GetFullPath()
	{
		return _sFullPath;
	}


	std::string CTask::GetDirProp()
	{
		return _sDirProp;
	}



	CDwn::CDwn() {}

	CDwn::CDwn(const std::string & WantFile, CTask  Task)
	{
		_WantFile = WantFile;
		_Task = Task;
	}



	bool CLogic::IsWork()
	{
		CSeting  Seting;

		std::string ActualWorkDir = GetActualWorkDir(Seting.GetWorkDir());
		//  D:\Development\booking\bin2\Debug\db\04.03.2020

		std::vector<std::experimental::filesystem::path> arrDir = CFileSystem::directory_iterator(ActualWorkDir);


		if ( arrDir.empty() )
		{
			return true;
		}

		std::vector<std::string> ArrIntrestingDir;

		for (auto it : arrDir)
		{
			std::string dir(it.string(), ActualWorkDir.size());

			if (dir.size() == 22)
				ArrIntrestingDir.push_back(it.string());
		}


		for (auto it : ArrIntrestingDir)
		{
			bool b = CDownload::IsPropuskDwnFile(it);

			if (b == true)
			{
				Log::CFileLog::Log("[CLogic::IsWork] : ne vse faili skacheni", LOG_LOGIC);
				return true;
			}
		}

		return false;
	}

	bool  CLogic::Work()
	{
		CSeting  Seting;

		bool bCreateDir = client::CLogic::CreateWorkDir(Seting.GetWorkDir());

		std::vector<CTask> TaskArr = client::CLogic::CreateTask(Seting);

		client::CLogic::CreateSettingForParser(TaskArr, Seting);

		bool bRunUtil = client::CLogic::RunUtilDownload(TaskArr, Seting);

		Log::CFileLog::Log("[CLogic::Work] : client::CLogic::RunUtilDownload = " + std::to_string(bRunUtil), LOG_LOGIC);
		  
		bRunUtil = client::CLogic::RunUtilParse(TaskArr, Seting);

		Log::CFileLog::Log("[CLogic::Work] : client::CLogic::RunUtilParse = " + std::to_string(bRunUtil) , LOG_LOGIC);

		return true;
	}

	bool CLogic::RunUtilParse(const std::vector<CTask> & TaskArr, CSeting Seting)
	{

		std::string sUtilName = "booking_html_parser.exe";

		int i = 0;

		for (auto it : TaskArr)
		{
			std::string cmd = Seting.GetProgaDir() + OS::CSystyem::GetSlash() + sUtilName + " " + it.GetDirProp() + " " + std::to_string(i);

			system(cmd.c_str());
		}

		return true;
	}

	std::vector<CTask> CLogic::CreateTask(CSeting Seting)
	{
		/*
		 cur-> 28.02.2020
		   request 01.03.2020-02.03.2020
		   request 01.03.2020-03.03.2020
		   request 01.03.2020-04.03.2020
		   request 01.03.2020-05.03.2020
		*/

		int DayRequest = Seting.GetDay();

		std::vector<CTask>  TaskArr;

		for (int i = 1; i <= DayRequest; i++)
		{
			int  DAY_NEXT = 1;
			Base::CData dat = L2::CData::GetStringCurrentDaraAndOffsetDay2(DAY_NEXT);
			Base::CData nextdat = L2::CData::GetStringCurrentDaraAndOffsetDay2(DAY_NEXT + i);


			// директория для парсера витала
			// D:\Development\booking\prod\28.02.2020\ X.X.X-X.X.X
			std::string sPropDir = Seting.GetWorkDirAndCurrentDay()
				+ OS::CSystyem::GetSlash()
				+ L2::CData::GetStringCurrentDaraAndOffsetDay(DAY_NEXT)  // X.X.X
				+ "-"
				+ L2::CData::GetStringCurrentDaraAndOffsetDay(DAY_NEXT + i); // X.X.X

			bool bCreate = CFileSystem::create_directories(sPropDir);

			//if (bCreate) { std::cout << "not create dir"; }

			std::string sPathProperies = sPropDir + OS::CSystyem::GetSlash() + "props.properties";

			Java::CProperties Properties(dat.startDay, dat.startMonth, dat.startYear, nextdat.startDay, nextdat.startMonth, nextdat.startYear, sPropDir);
			Properties.CreateProperties(sPathProperies);

			TaskArr.push_back(CTask(Properties, sPathProperies, sPropDir));

			std::cout << " call this run parser " << sPropDir << "\n";
		}

		return TaskArr;
	}

	bool CLogic::CreateWorkDir(const std::string & sDirPath)
	{
		std::string sDirName = L2::CData::GetStringCurrentDaraAndOffsetDay(0);

		return CFileSystem::create_directories(sDirPath + OS::CSystyem::GetSlash() + sDirName);
	}

	bool CLogic::UpdateFileProperties(std::string WantFile, std::string  GetFullPath, std::string  GetProgaDir)
	{
		if (std::experimental::filesystem::exists(WantFile))
		{
			std::cout << "[CLogic::RunUtilDownload] : del " << WantFile << "\n";
			std::experimental::filesystem::remove(WantFile);
		}

		std::cout << "[CLogic::RunUtilDownload] : copy " << GetFullPath << " to " << GetProgaDir << "\n";
		std::experimental::filesystem::copy(GetFullPath, GetProgaDir);
		return true;
	}

	bool CLogic::Download(std::string WantFile, CTask it, CDwn & ErrDwnArr)
	{
		// save imprintn before dwnload
		std::vector<std::experimental::filesystem::path> file_before = CFileSystem::directory_iterator(it.GetDirProp());

		{
			// call java util
			std::cout << "[CLogic::RunUtilDownload] : java -jar PARSER_x86.jar \n";
			system("java -jar PARSER_x86.jar");
		}


		// if download
		std::vector<std::experimental::filesystem::path> file_after = CFileSystem::directory_iterator(it.GetDirProp());

		std::cout << "[CLogic::RunUtilDownload] : : after" << file_after.size() << " before " << file_before.size() << "\n";
		if (file_after.size() > file_before.size())
		{
			for (auto it_dwn : file_after)
				std::cout << "[CLogic::RunUtilDownload] : BBG download: " << it_dwn << "\n";
		}
		else
		{
			CDwn dwn(WantFile, it);
			ErrDwnArr = dwn;
			std::cout << "[CLogic::RunUtilDownload] : not download by script: " << WantFile << ", Add this to replace dwn \n";
			return false;
		}

		return true;
	}

	bool CLogic::Thread_download(std::string WantFile, CTask it)
	{
		CDwn ErrDwnArr;
		bool bRet = Download(WantFile, it, ErrDwnArr);

		if (bRet == false)
		{
			std::cout << "RunUtilDownload : popitka dwnload #2\n";
			bRet = Download(WantFile, it, ErrDwnArr);
		}
		if (bRet == false)
		{
			std::cout << "RunUtilDownload : popitka dwnload #3\n";
			bRet = Download(WantFile, it, ErrDwnArr);
		}
		if (bRet == false)
		{
			std::cout << "RunUtilDownload : popitka dwnload #4\n";
			bRet = Download(WantFile, it, ErrDwnArr);
		}
		return bRet;
	}

	bool CLogic::CreateSettingForParser(const std::vector<CTask> & TaskArr, CSeting Seting)
	{
		std::stringstream ss;

		std::string  sFileName = "parser.ini";

		for (auto it : TaskArr)
			ss << it.GetDirProp() << "\n";


		std::string sPathSave = Seting.GetWorkDirAndCurrentDay() + OS::CSystyem::GetSlash() + sFileName;

		std::ofstream outFile(sPathSave);
		outFile << ss.rdbuf();
		outFile.close();

		return true;
	}

	bool CLogic::RunUtilDownload(const std::vector<CTask> & TaskArr, CSeting Seting)
	{
		std::vector <std::string> ErrDwnByScriptArr;

		for (CTask it : TaskArr)
		{
			// Replace file script
			std::string WantFile = Seting.GetProgaDir() + OS::CSystyem::GetSlash() + PROPERTIES;

			UpdateFileProperties(WantFile, it.GetFullPath(), Seting.GetProgaDir());

			Thread_download(WantFile, it);
		}
		return true;
	}


	std::string  CLogic::GetActualWorkDir(const std::string & sDirPath)
	{
		std::string sDirName = L2::CData::GetStringCurrentDaraAndOffsetDay(0);

		return  sDirPath + OS::CSystyem::GetSlash() + sDirName;
	}


}
