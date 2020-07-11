#include "def.h"

#include "DownloadModul.h"
#include "logic_impl.h"
#include "common.h"
#include <chrono>
#include <thread>

 
/*
	new variaan zapuska taskov, pri cotorom odna zadacha zapuskaets9 v fone, a vtora9 v tekuchem potoke.
*/

void RunInNewThread(const std::string cmd)
{
	Log::CFileLog::Log("new thread Task parse:  call: " + cmd, LOG_MAIN_PROD_PARSER);

	system(cmd.c_str());
	Log::CFileLog::Log("new thread End work: ", LOG_MAIN_PROD_PARSER);
}

int main()
{ 
	std::vector<std::string> ResultTargetDir = client::CLogic::get_path_for_run_utils();
	  
	int i = 0; 

	for (int i= 0; i< ResultTargetDir.size(); i++)
	{
		auto it = ResultTargetDir[i];
		std::string cmd = "booking_html_parser.exe " + it  + " c";		
		std::thread bckgroundThr(RunInNewThread, cmd);
		bckgroundThr.detach();
		Log::CFileLog::Log("Task parse: " + std::to_string(i) + "/" + std::to_string(ResultTargetDir.size()) + " call " + cmd, LOG_MAIN_PROD_PARSER);
		
		i++;
		it = ResultTargetDir[i];
		cmd = "booking_html_parser.exe " + it  + " c";
		Log::CFileLog::Log("main thread Task parse: " + std::to_string(i) + "/" + std::to_string(ResultTargetDir.size()) + " call " + cmd, LOG_MAIN_PROD_PARSER);
		 
		system(cmd.c_str());
	}
	return 0;
} 




