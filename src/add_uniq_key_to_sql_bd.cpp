//#include "def.h"
//

#include "calendar_data_provider.h"
#include "DownloadModul.h"
#include "calendar_def.h"
#include "logic_impl.h"
#include "common.h"
#include "calendar.h"
#include "foreach_dir.h"

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
		std::vector<std::string> Uniq_key = Level2::CDataProvider::get_all_uniq_key_fom_file ( it );
		i++;

		for (auto & itKeyApart : Uniq_key)
		{
			std::string s = "C:\\Qt\\5.9.9\\mingw53_32\\bin\\add_apart_key.exe"   " add "   "\"" + itKeyApart + "\""  ;
			system(s.c_str());
		}
	}
	 

	return 0;
}