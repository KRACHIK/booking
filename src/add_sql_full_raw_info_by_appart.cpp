#include "calendar.h"
#include <iostream>

#include "calendar_data_provider.h"
#include "DownloadModul.h"
#include "calendar_def.h"
#include "logic_impl.h"
#include "common.h"
#include "calendar.h"
 


#include <chrono>
#include <thread>


int main()
{
	std::vector<client::CTask> ReDownloadTaskArr;
	CDownLoadList  DownLoadList;
	client::CSeting  Seting;
	std::vector<std::string> level2dir = CWrapPath::get_all_level2_dir(DownLoadList, Seting);
	std::vector<std::string> level3dir = CWrapPath::get_all_level3_dir(DownLoadList, level2dir, Seting);
	int i = 0;

	for (auto it : level3dir)
	{  
		Log::CFileLog::Log("Task parse: " + std::to_string(i) + "/" + std::to_string(level3dir.size()) + " call ", LOG_MAIN_DATA_OB_ODNOM_OTELE);
		i++;
		 
		std::vector<CHomeNameAndCostAndData> Arr = Level2::CDataProvider::get_array_HomeNameAndCostAndData_by_file( it );

		if (i >= 287)
		{
		
		 //TASK 287| »« 1781 Œ“≈À‹ 52 »« 394

		int k = 0;
		for (auto apart : Arr)
		{
			std::string text = apart.Serialize();

			std::string APART_NAME = apart.GetHome().GetName();
			std::string APART_COST = std::to_string ( apart.GetHome().GetCost() ) ;
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
			  
			Log::CFileLog::Log("Task parse: <" + std::to_string(i) +"|" +std::to_string(level3dir.size()) + ">"
				+ " <" + std::to_string(Arr.size()) + "|" + std::to_string(++k) + ">   "
				+ s, LOG_MAIN_DATA_OB_ODNOM_OTELE);
			 
			system(s.c_str());

	 		}

		k = 0;
		}
	 
	}
	  
	return 0;
}


