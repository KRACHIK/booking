#include "def.h"

#include "DownloadModul.h"
#include "logic_impl.h"
#include "common.h"
#include <chrono>
#include <thread>


#define LOCAL_DEFINE_PROG_NAME "[MAIN_PROD_PARSER] "

/*
	new variaan zapuska taskov, pri cotorom odna zadacha zapuskaets9 v fone, a vtora9 v tekuchem potoke.
*/

void RunInNewThread(const std::string cmd)
{
	Log::CFileLog::Log("new thread Task parse:  call: " + cmd, LOG_MAIN_PROD_PARSER, LOCAL_DEFINE_PROG_NAME);

	 system(cmd.c_str());
	Log::CFileLog::Log("new thread End work: ", LOG_MAIN_PROD_PARSER, LOCAL_DEFINE_PROG_NAME);
}

int main()
{ 
	std::vector<std::string> ResultTargetDir = client::CLogic::get_path_for_run_utils();
	  
	 
	for (int i= 0; i< ResultTargetDir.size()-1/*fix! for before i++ in start two thread*/; i++)
	{
		auto it = ResultTargetDir[i];
		std::string cmd = "booking_html_parser.exe " + it  + " c";		
		std::thread bckgroundThr(RunInNewThread, cmd);
		bckgroundThr.detach();
		Log::CFileLog::Log("Task parse: " + std::to_string(i) + "/" + std::to_string(ResultTargetDir.size()) + " call " + cmd
			, LOG_MAIN_PROD_PARSER, LOCAL_DEFINE_PROG_NAME);
		
		i++; // <- 
		it = ResultTargetDir[i];
		cmd = "booking_html_parser.exe " + it  + " c";
		Log::CFileLog::Log("main thread Task parse: " + std::to_string(i) + "/" + std::to_string(ResultTargetDir.size()) + " call " + cmd
			, LOG_MAIN_PROD_PARSER, LOCAL_DEFINE_PROG_NAME);
		 
		system(cmd.c_str());
	}

	Log::CFileLog::Log("[main] End. (exit)", LOG_MAIN_PROD_PARSER, LOCAL_DEFINE_PROG_NAME);

	return 0;
} 




