#ifndef   COMMON_H
#define   COMMON_H

#include "def.h"
#include "calendar_def.h"


#include "Str.h"



#define FILE_DBG								"FILE_DBG"
#define ALL_NAME_HOTEL_BY_ALL_FILE_IN_THIS_DIR	"FILE_HOTEL_NAME_DB"
#define NAME_AND_COST							"FILE_NAME_AND_COST_DB"
#define FILE_NAME_SPY							"FILE_NAME_SPY"
//#define FILE_UNIQ_APART_KEY						"FILE_UNIQ_APART_KEY"
#define FILE_UNIQ_APART_KEY						"FILE_UNIQ_APART_KEY"
#define FILE_PROCESSING_INFO_RESULT				"FILE_PROCESSING_INFO_RESULT"
#define FILE_FORMAT								".kr4"


#define LOG_CALENDAR							"LOG_CALENDAR.log"
#define LOG_PARSER								"LOG_PARSER.log"
#define LOG_LOGIC								"LOG_LOGIC.log"
#define LOG_TOTAL_HOME_PARSER					"LOG_TOTAL_HOME_PARSER.log"

#define LOG_CALENDAR_ERR						"LOG_CALENDAR_ERR.log"
#define LOG_PARSER_ERR							"LOG_PARSER_ERR.log"
#define LOG_LOGIC_ERR							"LOG_LOGIC_ERR.log"
#define LOG_TOTAL_HOME_PARSER_ERR				"LOG_TOTAL_HOME_PARSER_ERR.log"

#define LOG_COMMON_ENGINE						"LOG_COMMON_ENGINE.log"

#define LOG_MAIN_PROD_PARSER					"LOG_MAIN_PROD_PARSER.log"
#define LOG_MAIN_DATA_OB_ODNOM_OTELE			"LOG_MAIN_DATA_OB_ODNOM_OTELE.log"



namespace Log {

	class CFileLog
	{
	public:
		static void Log(const std::string & Str, const std::string & sFileName);
		static void raw_log(const std::string & Str, const std::string & sFileName);
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

		std::string Serialize()
		{
			return  std::to_string(startDay) + "." + std::to_string(startMonth) + "." + std::to_string(startYear);
		}

		static bool Parse(const std::string & Src, CData & Start, CData & End);

		static bool Parse(const std::string & Src, CData & OutPutData);


		bool operator == (const Base::CData & right)
		{
			return (
				startDay == right.startDay &&
				startMonth == right.startMonth &&
				startYear == right.startYear
				);
		}

        static bool create_data_by_vector_int(const std::vector <int > & Arr, CData & OutPutStart, CData & OutPutEnd);

        static std::string get_str_for_excel(const CData & Start, const CData & End);

		bool operator ==(CData & d) 
		{
			return d.startYear == startYear
				&& d.startMonth == startMonth
				&& d.startDay == startDay;
		}

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

    class CTime
    {
    public:
        CTime(){}
        CTime(int  Hour,int  Min) : _Hour(Hour), _Min(Min) { }

    public:
        int _Hour;
        int _Min;
    };


	class CData
	{
	public:

		static std::string GetStringCurrentDaraAndOffsetDay(int ADD_DAYS);

		static Base::CData  GetStringCurrentDaraAndOffsetDay2(int ADD_DAYS);

		static Base::CData GetCurData();

        static void Time(int &Hour, int &Min);


        static CTime GetTime( );

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

		std::vector<std::string> & GetArrName()  { return  _ArrName; }

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


		void set_work_country_dir(const std::string & sPrefixDir);
		std::string get_work_country_dir() const { return  _sWorkCountryDir; }


        std::string get_download_list_file_path() const;

		void set_country(const std::string & sCountry) { _sCountry = sCountry; }
		std::string get_country() const { return _sCountry; }

        static bool IsTimeWork(CSeting &Seting);


        L2::CTime GetRunProgaInTime() const;

    private:
        std::string _sWorkDir;
        std::string _sProgaDir;
		std::string _sWorkCountryDir; //vichisl9emoe
		std::string _sCountry; //vichisl9emoe
        int _Day = 7;


        L2::CTime _RunProgaInTime = L2::CTime(10, 0);
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

		static std::vector<std::string>  get_all_uniq_key_fom_file(std::string sPath);

		static std::vector<std::string>  GetAllHotelName(std::string sPath);

		/*
			input:    path  D:\\Development\\booking\\bin2\\Debug\\db\\29.02.2020\\01.03.2020-04.03.2020"
			output    
		    new name get_files_name_and_cost old name GetArrHomeNameAndCost
		*/
		static std::vector<std::string> get_files_name_and_cost(std::string sPath);
		 
		static bool is_find_file_uniq_key(const std::string & sPath);
	 
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
		static std::string get_level2_name(const std::string & Path);
		static bool get_level2_data_obj(const std::string & Path, Base::CData & OutPutPresult);


	};
}
#endif 


namespace dir_path {

	class CParse
	{
	public:
        static std::string get_path_to_contry(const std::string & sDirDir);

        static std::string get_contry(const std::string & sDirDir);

	};

}


#endif /* COMMON_H */
