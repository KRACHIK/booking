#ifndef FOREACH_DIR
#define FOREACH_DIR

//#include "common.h"
 
#if defined(_WIN32) || defined(_WIN32_WCE) || defined(__WIN32__)
	#include <experimental/filesystem>
#else
	#include <experimental/filesystem>
#endif 

#include "common.h"
#include "DownloadModul.h"

#include <vector>
#include <string>

 
 
class CPathFuncs 
{

public:

static  std::vector<std::string> get_all_level1_dir(CDownLoadList & DownLoadList, client::CSeting  & Seting);

static std::vector<std::experimental::filesystem::path> get_all_level2_dir(CDownLoadList & DownLoadList, client::CSeting  & Seting);

static std::vector<std::experimental::filesystem::path> get_all_level3_dir(CDownLoadList & DownLoadList
	, std::vector<std::experimental::filesystem::path> level2dir, client::CSeting  & Seting);

 static std::vector<std::experimental::filesystem::path> get_all_level3_dir__(CDownLoadList & DownLoadList
 	                        , std::vector<std::string> level2dir, client::CSeting  & Seting);

};


class CWrapPath
{
public:
	static std::vector<std::string> get_all_level1_dir(CDownLoadList & DownLoadList, client::CSeting  & Seting);
		  
	static std::vector<std::string> get_all_level2_dir(CDownLoadList & DownLoadList, client::CSeting  & Seting);

	static std::vector<std::string> get_all_level3_dir(CDownLoadList & DownLoadList
														, std::vector<std::string> level2dir
														, client::CSeting  & Seting);
};






#endif /*FOREACH_DIR*/


