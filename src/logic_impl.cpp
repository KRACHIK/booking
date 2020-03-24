
#include "logic_impl.h"

#include <chrono>
#include <thread>


namespace client
{

	std::vector<std::experimental::filesystem::path>
		CLogic::get_all_level3_dir(CDownLoadList & DownLoadList
			, std::vector<std::experimental::filesystem::path> level2dir
			, CSeting  & Seting)
	{
		/*-------D:\Development\booking\bin2\Debug\db\-2326178\08.03.2020\09.03.2020-11.03.2020
		----------------------------------------------Levle-1----Levle-2---------Levle-3   */

		std::vector<std::experimental::filesystem::path> ArrIntrestingDir;


		for (auto it : level2dir)
		{
			std::vector<std::experimental::filesystem::path> arrDir = CFileSystem::directory_iterator(it.string());

			for (auto j : arrDir)
			{
				std::string dir(j.string(), it.string().size());
				int sfd;

				if (dir.size() == 22)
					ArrIntrestingDir.push_back(  j  );
			}
		}


		return ArrIntrestingDir;
	}


	std::vector<std::string> CLogic::get_all_level1_dir(CDownLoadList & DownLoadList, CSeting  & Seting)
	{
		/*-------D:\Development\booking\bin2\Debug\db\-2326178\08.03.2020\09.03.2020-11.03.2020
		----------------------------------------------Levle-1----Levle-2---------Levle-3   */
		 
		std::vector<std::string> arrDir;
		// Xodit po stranam
		for (auto it : DownLoadList.get_valid_link())
		{

			// set current country for setting object
			std::string  sCountryIndex;
			bool bRet = DownLoadList.get_dest_by_link(it, sCountryIndex);
			Seting.set_work_country_dir(sCountryIndex);
			Seting.set_country(sCountryIndex);

			std::string ActualWorkDir = Seting.GetWorkDir(); //D:\Development\booking\bin2\Debug\db\-2327363
			arrDir.push_back(ActualWorkDir);
				 
		}

		return arrDir;
	}


	std::vector<std::experimental::filesystem::path> CLogic::get_all_level2_dir(CDownLoadList & DownLoadList, CSeting  & Seting)
	{
		/*-------D:\Development\booking\bin2\Debug\db\-2326178\08.03.2020\09.03.2020-11.03.2020
		----------------------------------------------Levle-1----Levle-2---------Levle-3   */

		std::vector<std::experimental::filesystem::path> Ret;

		// Xodit po stranam
		for (auto it : DownLoadList.get_valid_link())
		{

			// set current country for setting object
			std::string  sCountryIndex;
			bool bRet = DownLoadList.get_dest_by_link(it, sCountryIndex);
			Seting.set_work_country_dir(sCountryIndex);
			Seting.set_country(sCountryIndex);

			std::string ActualWorkDir = Seting.GetWorkDir(); //D:\Development\booking\bin2\Debug\db\-2327363

			std::vector<std::experimental::filesystem::path> arrDir = CFileSystem::directory_iterator(ActualWorkDir);

			///filter get only tru dir
			for (auto t : arrDir)
			{
				std::string tru = std::string(t.string(), ActualWorkDir.size());

				if (tru.size() != 11) // target ---------------> "/08.03.2020"
				{
					continue;
				}
				else
				{
					//grab
					Ret.push_back(t);
				}
			}

		}

		return Ret;
	}

	bool  CLogic::IsPropuskDwnFile(CDownLoadList & DownLoadList, std::vector<client::CTask> & ReDownloadTaskArr, CSeting  & Seting)
	{

		// Xodit po stranam
		for (auto it : DownLoadList.get_valid_link())
		{

			// set current country for setting object
			std::string  sCountryIndex;
			bool bRet = DownLoadList.get_dest_by_link(it, sCountryIndex);
			Seting.set_work_country_dir(sCountryIndex);
			Seting.set_country(sCountryIndex);


			std::string ActualWorkDir = GetActualWorkDir(Seting.GetWorkDir()); //D:\Development\booking\bin2\Debug\db\04.03.2020

			std::vector<std::experimental::filesystem::path> arrDir = CFileSystem::directory_iterator(ActualWorkDir);


			if (arrDir.empty())
			{
				Log::CFileLog::Log("[CLogic::IsPropuskDwnFile] : files property not created, and request dir diapozon to created", LOG_LOGIC);
				return false;
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
				if (CDownload::IsPropuskDwnFile(it, ReDownloadTaskArr))
				{
					Log::CFileLog::Log("[CLogic::IsWork] : ne vse faili skacheni in dir " + it, LOG_LOGIC);
					//return true;
				}
			}
		}

		if (ReDownloadTaskArr.size() > 0)
			return true;
		else
			return false;

	}


	bool  CLogic::DwnPropuskFile(std::vector<client::CTask> & TaskArr)
	{
		CSeting  Seting;

		bool bRunUtil = client::CLogic::RunUtilDownload(TaskArr, Seting);

		Log::CFileLog::Log("[CLogic::Work] : CLogic::DwnPropuskFile = " + std::to_string(bRunUtil), LOG_LOGIC);

		return bRunUtil;
	}


	bool CLogic::IsWork(std::vector<client::CTask> & TaskArr)
	{
		CSeting  Seting;

		std::string ActualWorkDir = GetActualWorkDir(Seting.GetWorkDir()); //  D:\Development\booking\bin2\Debug\db\04.03.2020

		std::vector<std::experimental::filesystem::path> arrDir = CFileSystem::directory_iterator(ActualWorkDir);

		if (arrDir.empty())
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
			bool b = CDownload::IsPropuskDwnFile(it, TaskArr);

			if (b == true)
			{
				Log::CFileLog::Log("[CLogic::IsWork] : ne vse faili skacheni", LOG_LOGIC);
				//return true;
			}
		}

		return false;
	}




	bool CLogic::CreateTaskForMoreCountry(CDownLoadList & DownLoadList, std::vector<client::CTask> & TaskArr, CSeting & Seting)
	{
		for (auto it : DownLoadList.get_valid_link())
		{
			std::string  sCountryIndex;

			bool bRet = DownLoadList.get_dest_by_link(it, sCountryIndex);

			Seting.set_work_country_dir(sCountryIndex);

			Seting.set_country(sCountryIndex);

			bool bCreateDir = client::CLogic::CreateWorkDir(Seting.get_work_country_dir());

			std::vector<CTask> LocalTaskArr = client::CLogic::CreateTask(Seting);

			TaskArr.insert(TaskArr.begin(), LocalTaskArr.begin(), LocalTaskArr.end());
		}

		//bool bRunUtil = client::CLogic::RunUtilDownload(TaskArr, Seting);
		if (TaskArr.empty())
			return false;

		return true;
	}


	bool  CLogic::Work()
	{
		CSeting  Seting;

		bool bCreateDir = client::CLogic::CreateWorkDir(Seting.GetWorkDir());

#if 0
		std::vector<CTask> TaskArr = client::CLogic::CreateTask_v2_temp(Seting);
#else
		std::vector<CTask> TaskArr = client::CLogic::CreateTask(Seting); // old 
#endif

		client::CLogic::CreateSettingForParser(TaskArr, Seting);

		bool bRunUtil = client::CLogic::RunUtilDownload(TaskArr, Seting);

		Log::CFileLog::Log("[CLogic::Work] : client::CLogic::RunUtilDownload = " + std::to_string(bRunUtil), LOG_LOGIC);

		bRunUtil = client::CLogic::RunUtilParse(TaskArr, Seting);

		Log::CFileLog::Log("[CLogic::Work] : client::CLogic::RunUtilParse = " + std::to_string(bRunUtil), LOG_LOGIC);

		return true;
	}

	bool CLogic::RunUtilParse(const std::vector<CTask> & TaskArr, CSeting & Seting)
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
	 
	std::vector<CTask> CLogic::CreateTask_v2_temp(CSeting Seting)
	{
		/*
		 cur-> 28.02.2020
		   request 01.03.2020-02.03.2020
		   request 01.03.2020-03.03.2020
		   request 01.03.2020-04.03.2020
		   request 01.03.2020-05.03.2020
		*/

		int DayRequest = 360; // Seting.GetDay();

		std::vector<CTask>  TaskArr;


		for (int i = 1; i <= DayRequest; i++)
		{

			int  DAY_NEXT = i, DAY_OFFSET = 7;
			Base::CData dat = L2::CData::GetStringCurrentDaraAndOffsetDay2(DAY_NEXT);
			Base::CData nextdat = L2::CData::GetStringCurrentDaraAndOffsetDay2(DAY_NEXT + DAY_OFFSET);


			// директория для парсера витала
			// D:\Development\booking\prod\28.02.2020\ X.X.X-X.X.X
			std::string sPropDir = Seting.GetWorkDirAndCurrentDay()
				+ OS::CSystyem::GetSlash()
				+ L2::CData::GetStringCurrentDaraAndOffsetDay(DAY_NEXT)  // X.X.X
				+ "-"
				+ L2::CData::GetStringCurrentDaraAndOffsetDay(DAY_NEXT + DAY_OFFSET); // X.X.X

			bool bCreate = CFileSystem::create_directories(sPropDir);

			//if (bCreate) { std::cout << "not create dir"; }

			std::string sPathProperies = sPropDir + OS::CSystyem::GetSlash() + "props.properties";

			Java::CProperties Properties(dat.startDay, dat.startMonth, dat.startYear, nextdat.startDay, nextdat.startMonth, nextdat.startYear, sPropDir);
			Properties.CreateProperties(sPathProperies);

			TaskArr.push_back(CTask(Properties, sPathProperies, sPropDir));

		}

		return TaskArr;
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

			Java::CProperties Properties(dat.startDay, dat.startMonth, dat.startYear, nextdat.startDay, nextdat.startMonth, nextdat.startYear, sPropDir, Seting.get_country());
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
			Log::CFileLog::Log("[CLogic::RunUtilDownload] : del " + WantFile, LOG_LOGIC);
			std::experimental::filesystem::remove(WantFile);
		}

		Log::CFileLog::Log("[CLogic::RunUtilDownload] : copy " + GetFullPath + " to " + GetProgaDir, LOG_LOGIC);
		std::experimental::filesystem::copy(GetFullPath, GetProgaDir);

		return true;
	}

	bool CLogic::Download(std::string WantFile, CTask it, CDwn & ErrDwnArr)
	{
		// save imprintn before dwnload
		std::vector<std::experimental::filesystem::path> file_before = CFileSystem::directory_iterator(it.GetDirProp());

		int tRand = rand() % 5 + 1;
		Log::CFileLog::Log("[CLogic::RunUtilDownload] : java -jar PARSER_x86.jar this_thread::sleep_for " + std::to_string(tRand), LOG_LOGIC);

		std::this_thread::sleep_for(std::chrono::seconds(tRand));
		{
			// call java util
			system("java -jar PARSER_x86.jar");
		}


		// if download
		std::vector<std::experimental::filesystem::path> file_after = CFileSystem::directory_iterator(it.GetDirProp());

		//Log::CFileLog::Log("[CLogic::RunUtilDownload] : : after" + std::to_string(file_after.size()) + " before " + std::to_string(file_before.size()), LOG_LOGIC);

		if (file_after.size() > file_before.size())
		{
			for (auto it_dwn : file_after)
				Log::CFileLog::Log("[CLogic::RunUtilDownload] : BBG download: " + it_dwn.string(), LOG_LOGIC);
		}
		else
		{
			CDwn dwn(WantFile, it);
			ErrDwnArr = dwn;

			Log::CFileLog::Log("[CLogic::RunUtilDownload] : not download by script: " + WantFile + ", Add this to replace dwn " + it.GetFullPath(), LOG_LOGIC);

			return false;
		}



		return true;
	}

	bool CLogic::Thread_download(std::string WantFile, CTask it)
	{
		Log::CFileLog::Log("[CLogic::Thread_download] : " + WantFile, LOG_LOGIC);

		CDwn ErrDwnArr;
		bool bRet = Download(WantFile, it, ErrDwnArr);

		if (bRet == false)
		{
			Log::CFileLog::Log("[CLogic::Thread_download] : RunUtilDownload : popitka dwnload #2 " + WantFile, LOG_LOGIC);
			bRet = Download(WantFile, it, ErrDwnArr);
		}

		if (bRet == false)
		{
			Log::CFileLog::Log("[CLogic::Thread_download] : RunUtilDownload : popitka dwnload #3 " + WantFile, LOG_LOGIC);
			bRet = Download(WantFile, it, ErrDwnArr);
		}

		if (bRet == false)
		{
			Log::CFileLog::Log("[CLogic::Thread_download] : RunUtilDownload : popitka dwnload #4 " + WantFile, LOG_LOGIC);
			bRet = Download(WantFile, it, ErrDwnArr);
		}
		if (bRet == false)
		{
			Log::CFileLog::Log("[CLogic::Thread_download] : RunUtilDownload : popitka dwnload #5 " + WantFile, LOG_LOGIC);
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

	bool CLogic::RunUtilDownload(const std::vector<CTask> & TaskArr, CSeting & Seting)
	{
		std::vector <std::string> ErrDwnByScriptArr;
		int i = 0;
		for (CTask it : TaskArr)
		{
			// Replace file script
			std::string WantFile = Seting.GetProgaDir() + OS::CSystyem::GetSlash() + PROPERTIES;

			UpdateFileProperties(WantFile, it.GetFullPath(), Seting.GetProgaDir());

			Log::CFileLog::Log("[CLogic::Thread_download] : Task Number: " + std::to_string(i++) + " All Task " + std::to_string(TaskArr.size()), LOG_LOGIC);

			bool bDwn = Thread_download(WantFile, it);

			if (bDwn = false)
			{
				Log::CFileLog::Log("[CLogic::Thread_download] : " + WantFile, "Do_Dwnload.kr4");
			}

		}
		return true;
	}


	std::string  CLogic::GetActualWorkDir(const std::string & sDirPath)
	{
		std::string sDirName = L2::CData::GetStringCurrentDaraAndOffsetDay(0);

		return  sDirPath + OS::CSystyem::GetSlash() + sDirName;
	}


}
