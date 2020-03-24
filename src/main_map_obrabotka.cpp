#include "def.h"

#include "DownloadModul.h"
#include "logic_impl.h"
#include "common.h"

#include <chrono>
#include <thread>


#include "calendar.h"
#include <iostream>


int main()
{
	std::cout << " dsd\n";

	std::vector<client::CTask> ReDownloadTaskArr;
	CDownLoadList  DownLoadList;
	client::CSeting  Seting;
	std::vector<std::experimental::filesystem::path> level2dir = client::CLogic::get_all_level2_dir(DownLoadList, Seting);
	std::vector<std::experimental::filesystem::path> level3dir = client::CLogic::get_all_level3_dir(DownLoadList, level2dir, Seting);
	  
	client::IDataBase db;
	db.Init(level3dir);
	db.RenderStat();

	return 0;
}