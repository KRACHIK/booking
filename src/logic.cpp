

//#include "def.h"
//

#include "calendar_data_provider.h"
#include "DownloadModul.h"
#include "calendar_def.h"
#include "logic_impl.h"
#include "common.h"
#include "calendar.h"


#include <chrono>
#include <thread>



void utils_download()
{
	Log::CFileLog::Log("[utils_download] :  Start", LOG_LOGIC);
	system("MainDownloadManagerByFileList.exe");
	Log::CFileLog::Log("[utils_download] :  End", LOG_LOGIC);
}

void util_main_prod_parser()
{
	/* zapustit parser.
		parser sam opredelit? gde nujno vipolnit pars
	*/
	Log::CFileLog::Log("[util_parse] :  Start", LOG_LOGIC);
	system("main_prod_parser.exe");
	Log::CFileLog::Log("[util_parse] :  End", LOG_LOGIC);
}


void util_add_uniq_key_apart_to_sql_bd(std::vector<std::string> call_self_util_in_this_dir)
{
	Log::CFileLog::Log("[util_parse] :  Start", LOG_LOGIC);

	int i = 1;

	for (auto it : call_self_util_in_this_dir)
	{
		Log::CFileLog::Log("Task parse: " + std::to_string(i) + "/" + std::to_string(call_self_util_in_this_dir.size()) + " ", LOG_MAIN_DATA_OB_ODNOM_OTELE);

		std::vector<std::string> Uniq_key = Level2::CDataProvider::get_all_uniq_key_fom_file(it);

		i++;

		for (auto & itKeyApart : Uniq_key)
		{
			std::string s = "C:\\Qt\\5.9.9\\mingw53_32\\bin\\add_apart_key.exe"   " add "   "\"" + itKeyApart + "\"";
			system(s.c_str());
		}
	}

	Log::CFileLog::Log("[util_parse] :  End", LOG_LOGIC);
}


void util_add_raw_info_by_apart_to_sql_bd(std::vector<std::string> call_self_util_in_this_dir)
{
	Log::CFileLog::Log("[util_add_raw_info_by_apart_to_sql_bd] :  Start", LOG_LOGIC);

	int i = 1;
   
	for (auto it : call_self_util_in_this_dir)
	{
		Log::CFileLog::Log("Task parse: " + std::to_string(i) + "/" + std::to_string(call_self_util_in_this_dir.size()) + " call ", LOG_MAIN_DATA_OB_ODNOM_OTELE);
		
		i++;

		std::vector<CHomeNameAndCostAndData> Arr = Level2::CDataProvider::get_array_HomeNameAndCostAndData_by_file(it);
		  

		int k = 0;
		for (auto apart : Arr)
		{
			std::string text = apart.Serialize();

			std::string APART_NAME = apart.GetHome().GetName();
			std::string APART_COST = std::to_string(apart.GetHome().GetCost());
			std::string APART_UNIQ_KEY = apart.GetHome().create_qniq_key();
			std::string DATA_REQ = apart.get_Level2_data().Serialize();
			std::string DATA_START = apart.GetDataStart().Serialize();
			std::string DATA_END = apart.GetDataEnd().Serialize();

			std::string s = "C:\\Qt\\5.9.9\\mingw53_32\\bin\\sql_add_raw_full_info_apart.exe"
				" " "\"" + APART_NAME + "\""
				" " "\"" + APART_COST + "\""
				" " "\"" + APART_UNIQ_KEY + "\""
				" " "\"" + DATA_REQ + "\""
				" " "\"" + DATA_START + "\""
				" " "\"" + DATA_END + "\""
				" " "\"" + it  + "\"";

			Log::CFileLog::Log("Task parse: <" + std::to_string(i) + "|" + std::to_string(call_self_util_in_this_dir.size()) + ">"
				+ " <" + std::to_string(Arr.size()) + "|" + std::to_string(++k) + ">   "
				+ s, LOG_MAIN_DATA_OB_ODNOM_OTELE);

			system(s.c_str());

		}

		k = 0;
	}























	Log::CFileLog::Log("[util_add_raw_info_by_apart_to_sql_bd] :  End", LOG_LOGIC);
}


void util_create_calendar_in_sql() 
{
	Log::CFileLog::Log("[util_create_calendar_in_sql] :  Start", LOG_LOGIC);
	Log::CFileLog::Log("[util_create_calendar_in_sql] :  ZAGLUSHKA", LOG_LOGIC);
	Log::CFileLog::Log("[util_create_calendar_in_sql] :  End", LOG_LOGIC);
}



int main()
{
	/**/
	// 0 call utils download
	utils_download();
	
	// tmp save insrasing dir by 
	std::vector<std::string> intresting_dir = client::CLogic::get_path_for_run_utils();

	util_main_prod_parser();
	 
	util_add_uniq_key_apart_to_sql_bd(intresting_dir);
	
	util_add_raw_info_by_apart_to_sql_bd(intresting_dir);

	util_create_calendar_in_sql();

	return 0;
}



/*
 1 call util parse
 2 call util add uniq_key_apart to sql bd
 3 call util add raw_info by apart to sql bd
 4 call util createcalendar in sql
*/


