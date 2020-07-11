#include "def.h"

#include "DownloadModul.h"
#include "logic_impl.h"
#include "common.h"

#include <chrono>
#include <thread>


#include "calendar.h"
#include <iostream>


void Write_Hotel_to_DB()
{
	std::vector<client::CTask> ReDownloadTaskArr;
	CDownLoadList  DownLoadList;
	client::CSeting  Seting;
	std::vector<std::string> level2dir = CWrapPath::get_all_level2_dir(DownLoadList, Seting);
	std::vector<std::string> level3dir = CWrapPath::get_all_level3_dir(DownLoadList, level2dir, Seting);


	client::IDataBase db;
	db.Init_all_name(level3dir);

	db.Write_All_Hotel_to_db(level3dir);
}


void Read_Hotel_from_db()
{
	client::IDataBase db;
	std::vector<client::CTask> ReDownloadTaskArr;
	CDownLoadList  DownLoadList;
	client::CSeting  Seting;
	std::vector<std::string> level2dir = CWrapPath::get_all_level2_dir(DownLoadList, Seting);
	std::vector<std::string> level3dir = CWrapPath::get_all_level3_dir(DownLoadList, level2dir, Seting);
	

	db.Init_all_name(level3dir);

	db.Deserealize("yeah.txt");

	db.create_db_for_vital();

	int dfs234 = 23;
}


int main()
{

	if (0)
		Write_Hotel_to_DB();

	if (1)
		Read_Hotel_from_db();

	return 0;
}