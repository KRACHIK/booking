#ifndef FILE_H
#define FILE_H

#include "def.h"
//#include "common.h" // bad!

#include <string>
#include <iostream>


#if defined(_WIN32) || defined(_WIN32_WCE) || defined(__WIN32__)
    //#include <filesystem>
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



#include "calendar_def.h"


class CFileData
{
public:
	CFileData(const std::string & sFileName);

	std::vector<std::string> GetArrLine() const { return _ArrName; }

private:
	void Open(const std::string & sFileName);

private:
	std::string _sFileName;
	std::vector<std::string> _ArrName;
};

class CFileSystem
{
public:
	static bool IsEmptyFile(const std::experimental::filesystem::path & sPath)
	{
		std::error_code er;
		uintmax_t size = std::experimental::filesystem::file_size(  sPath, er);
		
		if (er)
			return false;

		if (size)
			return true;

		return false;
	}

    static std::string GetFileNameByPath(const std::string & sPath);


    static std::string  GetStemByPath(const std::string & sPath);


	static std::vector<std::string> GetFileByMask(const std::string & sPath, const std::string & sMask);

	static bool create_directories(const std::string & sMask);

	static std::vector<std::string> Filter(std::vector<std::experimental::filesystem::path> Arr
		, const std::string & sMask
	);


	static std::vector<std::experimental::filesystem::path>
		directory_iterator(const std::string & path);
};

#endif 
