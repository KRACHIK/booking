#include "def.h"
#include "common.h"
 

/*  
#include <iostream>
#include <assert.h>
#include <iomanip>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "file.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
*/

#if 0
namespace OS {
	class CSystyem
	{
	public:
		static std::string GetSlash()
		{
			//return "\\";
			return "//";
		}
	};
}
namespace Base{

	class CData
	{
	public:
		int startDay;
		int startMonth;
		int startYear;

	};
}
#endif 


namespace Java {

#define PROPERTIES "props.properties"

	class CProperties
	{
	public:
		CProperties() {}

		CProperties(
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
	public:

		void CreateProperties(std::string sFileName)
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

	private:
		int _startDay;
		int _startMonth;
		int _startYear;
		int _endDay;
		int _endMonth;
		int _endYear;
		std::string _outputDirectory;

	};

}

#if 0
namespace L2
{ 
	class CData
	{
	public:

		static std::string GetStringCurrentDaraAndOffsetDay(int ADD_DAYS)
		{
			struct tm *u;
			char s1[40] = { 0 }, s2[40] = { 0 };
			const time_t timer = time(NULL);
			u = localtime(&timer);
			strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", u);
			u->tm_mday += ADD_DAYS;
			time_t next = mktime(u);
			u = localtime(&next);
			strftime(s2, 80, "%d.%m.%Y", u);

			return  std::string(s2);
		}

		static Base::CData  GetStringCurrentDaraAndOffsetDay2(int ADD_DAYS)
		{
			struct tm *u;
			char  day[40] = { 0 }, month[40] = { 0 }, year[40] = { 0 };

			const time_t timer = time(NULL);
			u = localtime(&timer);
			u->tm_mday += ADD_DAYS;
			time_t next = mktime(u);
			u = localtime(&next);

			strftime(day, 80, "%d ", u);
			strftime(month, 80, "%m", u);
			strftime(year, 80, "%Y", u);

			Base::CData da;
			da.startDay = std::stoi(day);
			da.startMonth = std::stoi(month);
			da.startYear = std::stoi(year);

			return da;
		}



		static Base::CData GetCurData()
		{
			struct tm *u;
			char  day[40] = { 0 }, month[40] = { 0 }, year[40] = { 0 };
			const time_t timer = time(NULL);
			u = localtime(&timer);


			strftime(day, 80, "%d ", u);
			strftime(month, 80, "%m", u);
			strftime(year, 80, "%Y", u);

			Base::CData da;

			da.startDay = std::stoi(day);
			da.startMonth = std::stoi(month);
			da.startYear = std::stoi(year);

			return da;
		}


	};
}
#endif 

namespace client
{
	class CTask
	{
	public:

		CTask()
		{
		}

		CTask(Java::CProperties Properties
			, const std::string & sFullPath,
			const std::string  & sDirProp
		)
			: _Properties(Properties)
			, _sFullPath(sFullPath)
			, _sDirProp(sDirProp)
		{

		}

		std::string GetFullPath() const
		{
			return _sFullPath;
		}


		std::string GetDirProp() const
		{
			return _sDirProp;
		}
	private:

		Java::CProperties _Properties;
		std::string  _sFullPath;
		std::string  _sDirProp;

	};

	class CDwn
	{
	public:
		CDwn() {}

		CDwn(const std::string & WantFile, CTask  Task)
		{
			_WantFile = WantFile;
			_Task = Task;
		}

	public:
		std::string _WantFile;
		CTask _Task;
	};

#if 0
	class CSeting
	{
	public:
		CSeting()
		{
			_sWorkDir = "D://Development//booking//bin2//Debug//db";
			_sProgaDir = "D://Development//booking//bin2//Debug";
		}

		std::string GetProgaDir() const
		{
			return _sProgaDir;
		}

		int GetDay() const
		{
			return _Day;
		}

		std::string GetWorkDir() const
		{
			return _sWorkDir;
		}

		std::string GetWorkDirAndCurrentDay() const
		{
			std::string sPropDirName = GetWorkDir() + OS::CSystyem::GetSlash() + L2::CData::GetStringCurrentDaraAndOffsetDay(0);
			return sPropDirName;
		}

	private:
		std::string _sWorkDir;
		std::string _sProgaDir;

		int _Day = 3;
	};
#endif
	class CLogic
	{
	public:
		static bool IsWork()
		{
			return true;
		}

		static bool  Work()
		{
			CSeting  Seting;

			bool bCreateDir = client::CLogic::CreateWorkDir(Seting.GetWorkDir());

			//if (!bCreateDir) { std::cout << "not create work dir \n"; }

			std::vector<CTask> TaskArr = client::CLogic::CreateTask(Seting);

			client::CLogic::CreateSettingForParser(TaskArr, Seting);
			  
			bool bRunUtil = client::CLogic::RunUtilDownload(TaskArr, Seting);

			if (!bRunUtil) { std::cout << "not bRunUtil \n"; }

			return true;
		}

	private:


		static std::vector<CTask> CreateTask(CSeting Seting)
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


		static bool CreateWorkDir(const std::string & sDirPath)
		{
			std::string sDirName = L2::CData::GetStringCurrentDaraAndOffsetDay(0);

			return CFileSystem::create_directories(sDirPath + OS::CSystyem::GetSlash() + sDirName);
		}


		static bool UpdateFileProperties(std::string WantFile, std::string  GetFullPath, std::string  GetProgaDir)
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

		static bool Download(std::string WantFile, CTask it, CDwn & ErrDwnArr)
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

		static bool Thread_download(std::string WantFile, CTask it)
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

		static bool CreateSettingForParser(const std::vector<CTask> & TaskArr, CSeting Seting)
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

		static bool RunUtilDownload(const std::vector<CTask> & TaskArr, CSeting Seting)
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
	};

}

void Data1()
{
	std::time_t t = std::time(0);
	std::tm * local = std::localtime(&t);
	std::cout << "data = " << std::put_time(local, "%F") << std::endl;
	std::cout << "time = " << std::put_time(local, "%T") << std::endl;
}


void Dataa2()
{
	struct tm *u;
	char s1[40] = { 0 }, s2[40] = { 0 };
	const time_t timer = time(NULL);
	u = localtime(&timer);
	strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", u);
	printf("%s\n", s1);
#define ADD_DAYS 3
	u->tm_mday += ADD_DAYS;
	time_t next = mktime(u);
	u = localtime(&next);
	strftime(s2, 80, "%d.%m.%Y %H:%M:%S ", u);
	printf("%s\n", s2);
	getchar();
}

int main()
{

	//while (true)
	{
		if (client::CLogic::IsWork())
		{
			client::CLogic::Work();
		}
	}


	// 1 если нужно работаь
	// 2 сформировать рабочие каталоги
			// получить задание
			// получить текущую дату
			// получить дату на n дней вперед
	// 3 вызвать утилиты скачивания и парса
	// 4 ожидать задания


	return 0;
}