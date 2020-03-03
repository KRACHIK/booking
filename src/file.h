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
	CFileData(const std::string & sFileName)
		: _sFileName(sFileName)
	{
		Open(sFileName);
	}

	std::vector<std::string> GetArrLine() const { return _ArrName; }

private:

	void Open(const std::string & sFileName)
	{
		 CStr line;
		 
		 std::ifstream in(sFileName);
		 
		 if (in.is_open())
		 {
		 	while (getline(in, line))
		 	{
		 		_ArrName.push_back(line);
		 	}
		 }
		 else
		 {
		 	//Log::CFileLog::Log("Error Open file " + sFileName,  "Error.txt");
		 }
		 in.close();
	}

private:
	std::string _sFileName;
	std::vector<std::string> _ArrName;
};

class CFileSystem
{
public:


	static std::vector<std::string> GetFileByMask(const std::string & sPath, const std::string & sMask)
	{

		std::vector<std::experimental::filesystem::path> Arr  = directory_iterator(sPath);
		 
		std::vector<std::string> ResultIntrestingFile = Filter(Arr, sMask);

		return ResultIntrestingFile;
	}

	static bool create_directories(const std::string & sMask)
	{
		std::cout << "[CFileSystem::create_directories] " << sMask << "\n";

		bool bRet = std::experimental::filesystem::create_directories(sMask);

		return bRet;
	}

	static std::vector<std::string> Filter(
		std::vector<std::experimental::filesystem::path> Arr
		, const std::string & sMask
	)
	{
		std::vector<std::string> NewArr;

		for (auto & it : Arr)
		{
			std::string sPath = it.string();

			std::size_t found = sPath.find(sMask);

			if (found != std::string::npos)
			{
				NewArr.push_back(sPath);
			}
		}

		return NewArr;
	}




	static std::vector<std::experimental::filesystem::path> directory_iterator(const std::string & path)
	{
		//std::string path = "D:\\Development\\booking\\bin";

		std::vector<std::experimental::filesystem::path> Arr;

		for (auto & p : std::experimental::filesystem::directory_iterator(path))
		{
			Arr.push_back(p);
		}

		return Arr;
	}
};

#endif 
