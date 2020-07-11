#ifndef FILE_H
#define FILE_H

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
 

#endif 
