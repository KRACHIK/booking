#ifndef   COMMON_H
#define   COMMON_H

#include "def.h"

#include "calendar_def.h"

#include "Str.h"



#define ALL_NAME_HOTEL_BY_ALL_FILE_IN_THIS_DIR	"ALL_NAME_HOTEL_BY_ALL_FILE_IN_THIS_DIR"
#define NAME_AND_COST							"NAME_AND_COST_FILE"

#define LOG_CALENDAR		"LOG_CALENDAR.log"
#define LOG_PARSER			"LOG_PARSER.log"
#define LOG_LOGIC			"LOG_LOGIC.log"

#define LOG_CALENDAR_ERR	"LOG_CALENDAR_ERR.log"
#define LOG_PARSER_ERR		"LOG_PARSER_ERR.log"
#define LOG_LOGIC_ERR		"LOG_LOGIC_ERR.log"

namespace Log {

	class CFileLog
	{
	public:
		static void Log(const std::string & Str, const std::string & sFileName)
		{
			struct tm *u;
			char s1[40] = { 0 }, s2[40] = { 0 };
			const time_t timer = time(NULL);
			u = localtime(&timer);
			strftime(s1, 80, "[%d.%m.%Y %H:%M:%S] ", u);

			std::stringstream ss;

			ss << s1 << Str << "\n";

			std::ofstream outFile(sFileName, std::ios::app);
			outFile << ss.rdbuf();
			outFile.close();

			std::cout << s1 << Str << "\n";
		}

	};

}

namespace Base
{

	class CData
	{
	public:

		CData() {}

		CData(int startDay_, int startMonth_, int startYear_)
			: startDay(startDay_)
			, startMonth(startMonth_)
			, startYear(startYear_)
		{

		}

		static bool Parse(const std::string & Src, CData & Start, CData & End)
		{
			dati d = Str::rENAME::Parse_GetDataByPath(Src);

			if (d.size() != 6)
			{
				return false;
			}

			Start = CData(d[0], d[1], d[2]);
			End = CData(d[3], d[4], d[5]);

			return  true;
		}

	public:
		int startDay;
		int startMonth;
		int startYear;
	};


	class CUtil
	{
	public:

		static std::string GetDirByFilePath(const std::string & sGrabDirByFilePath, const CStr & sFileName)
		{
			struct tm *u;
			char s1[40] = { 0 }, s2[40] = { 0 };
			const time_t timer = time(NULL);
			u = localtime(&timer);
			strftime(s1, 80, "%d.%m.%Y_%H-%M-%S ", u);

			std::size_t found = sGrabDirByFilePath.find(".html");
			std::string Path;
			if (found != std::string::npos)
			{
				Path = std::string(sGrabDirByFilePath, 0, found) + "_" + sFileName + s1 + ".txt";
			}
			return Path;
		}

		static std::string GetDirByFilePath(std::string sFileHTML)
		{
			struct tm *u;
			char s1[40] = { 0 }, s2[40] = { 0 };
			const time_t timer = time(NULL);
			u = localtime(&timer);
			strftime(s1, 80, "%d.%m.%Y_%H-%M-%S ", u);

			std::size_t found = sFileHTML.find(".html");
			std::string Path;
			if (found != std::string::npos)
			{
				Path = std::string(sFileHTML, 0, found) + "_" + s1 + ".txt";
			}
			return Path;
		}

	};


}

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




namespace client
{

	class CAllNameFile
	{
	public:
		CAllNameFile(const std::string & sFileName)
			: _sFileName(sFileName)
		{
			Open(sFileName);
		}

		std::vector<std::string> GetArrName() const { return _ArrName; }

	private:

		void Open(const std::string & sFileName)
		{
			CStr line;
			std::ifstream in(sFileName);

			if (in.is_open())
			{
				while (getline(in, line))
				{
					_ArrName.push_back(line);
				}
			}
			else
			{
				Log::CFileLog::Log("Error Open file " + sFileName, LOG_CALENDAR_ERR);
			}
			in.close();
		}

	private:
		std::string _sFileName;
		std::vector<std::string> _ArrName;
	};

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

	class CHotel
	{
	public:
		CHotel(
			std::string  sName
			, int  Cost
			, Base::CData DayStart
			, Base::CData DayEnd
		)
		{
			_sName = sName;
			_Cost = Cost;
			_DayStart = DayStart;
			_DayEnd = DayEnd;
		}

		std::string GetDataString()
		{
			return std::string(
				std::to_string(_DayStart.startDay) + "." +
				std::to_string(_DayStart.startMonth) + "." +
				std::to_string(_DayStart.startYear) +
				"-" +
				std::to_string(_DayEnd.startDay) + "." +
				std::to_string(_DayEnd.startMonth) + "." +
				std::to_string(_DayEnd.startYear)
			);

		}

	public:
		std::string _sName;
		int _Cost;
		Base::CData _DayStart;
		Base::CData _DayEnd;
	};

	class CFileManager
	{
	public:

		static ArrHomeName  GetAllHotelName(std::string sPath)
		{
			//std::vector<std::string>  
			return  CFileSystem::GetFileByMask(sPath, ALL_NAME_HOTEL_BY_ALL_FILE_IN_THIS_DIR);
		}

		static ArrHomeName GetArrHomeNameAndCost(std::string sPath)
		{
			//std::vector<std::string>  
			return  CFileSystem::GetFileByMask(sPath, NAME_AND_COST);
		}



	};

}

#endif /* COMMON_H */
