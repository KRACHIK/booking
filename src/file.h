#ifndef FILE_H
#define FILE_H

#include "def.h"
//#include "common.h" // bad!

#include <string>
#include <iostream>
#include <filesystem>

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

	static std::vector<std::string> GetFileByMask(const std::string & sPath, const std::string & sMask);

	static bool create_directories(const std::string & sMask);

	static std::vector<std::string> Filter(
		std::vector<std::experimental::filesystem::path> Arr
		, const std::string & sMask
	);


	static std::vector<std::experimental::filesystem::path>
		directory_iterator(const std::string & path);
};

#endif 
