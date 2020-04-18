
#include "file.h"

CFileData::CFileData(const std::string & sFileName)
	: _sFileName(sFileName)
{
	Open(sFileName);
}


void CFileData::Open(const std::string & sFileName)
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


std::string CFileSystem::GetFileNameByPath(const std::string &sPath)
{
    std::experimental::filesystem::path p(sPath);
    //"c://dir/dir//file.ext"
    //std::cout << "filename and extension: " << p.filename() << std::endl; // "file.ext"
    return p.filename().string();
}

std::string CFileSystem::GetStemByPath(const std::string &sPath)
{
    std::experimental::filesystem::path p(sPath);
    //"c://dir/dir//file.ext"
    //std::cout << "filename only: " << p.stem() << std::endl;              // "file"
    return p.stem().string();
}

std::vector<std::string> CFileSystem::GetFileByMask(const std::string & sPath, const std::string & sMask)
{

    std::vector<std::experimental::filesystem::path> Arr = directory_iterator(sPath);

    std::vector<std::string> ResultIntrestingFile = Filter(Arr, sMask);

    return ResultIntrestingFile;
}

bool CFileSystem::create_directories(const std::string & sMask)
{
	std::cout << "[CFileSystem::create_directories] " << sMask << "\n";

    //bool bRet = std::experimental::filesystem::create_directories(sMask);
    bool bRet = std::experimental::filesystem::create_directories(sMask);

	return bRet;
}


 



std::vector<std::string> CFileSystem::Filter(
	std::vector<std::experimental::filesystem::path> Arr, const std::string & sMask)
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

std::vector<std::experimental::filesystem::path>
CFileSystem::directory_iterator(const std::string & path)
{
	//std::string path = "D:\\Development\\booking\\bin";
    if (!std::experimental::filesystem::exists(path)    )
    {
        return {};
    }


	std::vector<std::experimental::filesystem::path> Arr;
	 

	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		Arr.push_back(p);
	}

	return Arr;
}

