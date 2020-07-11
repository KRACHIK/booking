#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "def.h"
//#include "common.h" // bad!

#include <string>
#include <iostream>


#if defined(_WIN32) || defined(_WIN32_WCE) || defined(__WIN32__)
	#include <experimental/filesystem>
#else
	#include <experimental/filesystem>
#endif

/*
#ifdef LINUX
#else
#endif*/


#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "calendar_def.h"
 

class CFileSystem
{
public:
	static bool IsEmptyFile(const std::experimental::filesystem::path & sPath);

	static std::string GetFileNameByPath(const std::string & sPath);

	static std::string  GetStemByPath(const std::string & sPath);
 
	static std::vector<std::string> GetFileByMask(const std::string & sPath, const std::string & sMask);

	static bool create_directories(const std::string & sMask);

	static std::vector<std::string> Filter(std::vector<std::experimental::filesystem::path> Arr
		, const std::string & sMask
	);

	static std::vector<std::string> Filter(std::vector<std::string> Arr
		, const std::string & sMask
	);

	static std::vector<std::experimental::filesystem::path> directory_iterator(const std::string & path);
	 
	static std::vector<std::string> get_directory_iterator(const std::string & path);
	 
};

#endif 
