#ifndef   COMMON_H
#define   COMMON_H

#include "def.h"
#include "calendar_def.h"


#include "Str.h"



#define FILE_DBG								"FILE_DBG"
#define ALL_NAME_HOTEL_BY_ALL_FILE_IN_THIS_DIR	"FILE_HOTEL_NAME_DB"
#define NAME_AND_COST							"FILE_NAME_AND_COST_DB"
#define FILE_FORMAT								".kr4"

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
		static void Log(const std::string & Str, const std::string & sFileName);

	};

}

namespace Base
{
#if 1
	class CData
	{
	public:

		CData();
		CData(int startDay_, int startMonth_, int startYear_);

		static bool Parse(const std::string & Src, CData & Start, CData & End);

	public:
		int startDay;
		int startMonth;
		int startYear;
	};
#endif 

	class CUtil
	{
	public:

		static std::string GetDirByFilePath(const std::string & sGrabDirByFilePath, const CStr & sFileName);

		static std::string GetDirByFilePath(std::string sFileHTML);

	};


}

namespace L2
{
	class CData
	{
	public:

		static std::string GetStringCurrentDaraAndOffsetDay(int ADD_DAYS);

		static Base::CData  GetStringCurrentDaraAndOffsetDay2(int ADD_DAYS);

		static Base::CData GetCurData();

	};
}

namespace OS {
	class CSystyem
	{
	public:
		static std::string GetSlash();
	};
}




namespace client
{

	class CAllNameFile
	{
	public:
		CAllNameFile(const std::string & sFileName);

		std::vector<std::string> GetArrName() const { return _ArrName; }

	private:

		void Open(const std::string & sFileName);

	private:
		std::string _sFileName;
		std::vector<std::string> _ArrName;
	};

	class CSeting
	{
	public:
		CSeting();

		std::string GetProgaDir() const;
		int GetDay() const;

		std::string GetWorkDir() const;

		std::string GetWorkDirAndCurrentDay() const;

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
		);
		std::string GetDataString();

	public:
		std::string _sName;
		int _Cost;
		Base::CData _DayStart;
		Base::CData _DayEnd;
	};

	class CFileManager
	{
	public:

		static ArrHomeName  GetAllHotelName(std::string sPath);

		static ArrHomeName GetArrHomeNameAndCost(std::string sPath);


	};

}


#if  1 
namespace Str
{
	class Util
	{
	public:

		static std::vector <CStr> Parse_Space(const std::string & buf);
		static std::string do_replace(const std::string & in, const std::string &from, const std::string & to);
		static bool Parse_GetDataByPath(const std::string & buf, Base::CData & Start, Base::CData & End);
	};
}
#endif 


#endif /* COMMON_H */
