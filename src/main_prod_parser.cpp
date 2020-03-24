#include "def.h"

#include "DownloadModul.h"
#include "logic_impl.h"
#include "common.h"
#include <chrono>
#include <thread>


#if 0
int main()
{

	std::vector<client::CTask> ReDownloadTaskArr;
	CDownLoadList  DownLoadList;
	client::CSeting  Seting;


	std::vector<std::experimental::filesystem::path> level2dir = client::CLogic::get_all_level2_dir(DownLoadList, Seting);

	std::vector<std::experimental::filesystem::path> level3dir = client::CLogic::get_all_level3_dir(DownLoadList, level2dir, Seting);

	int i = 0;
	for (auto it : level3dir)
	{
		std::string cmd = "booking_html_parser.exe " + it.string() + " c";

		Log::CFileLog::Log("Task parse: " + std::to_string(i) + "/" + std::to_string(level3dir.size()) + " call " + cmd, LOG_MAIN_PROD_PARSER);
		i++;
		system(cmd.c_str());
	}
	return 0;
}
#else


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





