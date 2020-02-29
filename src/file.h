#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>
#include <filesystem>


class CFileSystem
{
public:


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
