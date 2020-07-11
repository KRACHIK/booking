#include "def.h"

#include "DownloadModul.h"
#include "logic_impl.h"
#include "common.h"
#include <chrono>
#include <thread>


#if 1
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
#else

 /*
	old variant zapuska taskov, pri cotorom porojdaets9 beskonechnoe chislo procesov
 
 */
#include <iostream>
#include <future>
#include <vector>
#include <chrono>
#include <string>

unsigned long long fib(const std::string & sFilePath, int cur, int allsize)
{

	Log::CFileLog::Log("Task parse: " + std::to_string(cur) + "/" + std::to_string(allsize) + " call " + sFilePath, LOG_MAIN_PROD_PARSER);

	system(sFilePath.c_str());

	return 1;
}

int main()
{
	std::vector<client::CTask> ReDownloadTaskArr;
	CDownLoadList  DownLoadList;
	client::CSeting  Seting;


	std::vector<std::experimental::filesystem::path> level2dir = client::CLogic::get_all_level2_dir(DownLoadList, Seting);
	std::vector<std::experimental::filesystem::path> level3dir = client::CLogic::get_all_level3_dir(DownLoadList, level2dir, Seting);

	std::vector<std::string> sTask;
	for (auto it : level3dir)
	{
		std::string cmd = "booking_html_parser.exe " + it.string() + " c";
		sTask.push_back(cmd);
	}

	 
	const unsigned numberOfTask = sTask.size();
	unsigned n = 0;
	std::vector<std::future<unsigned long long>> futures(numberOfTask);

	for (auto& f : futures)
	{
		f = std::async(std::launch::async, fib, sTask[n], n, sTask.size());
		n++;
	}


	for (auto& f : futures)
		std::cout << "f.get()=" << f.get() << "\n";

	return 0;
}



#endif 





