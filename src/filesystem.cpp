
#include "filesystem.h"


bool CFileSystem::IsEmptyFile(const std::experimental::filesystem::path & sPath)
{
	std::error_code er;
	uintmax_t size = std::experimental::filesystem::file_size(sPath, er);

	if (er)
		return false;

	if (size)
		return true;

	return false;
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

static std::vector<std::string> Filter(std::vector<std::string> Arr
	, const std::string & sMask
)
{
	std::vector<std::string> NewArr;

	for (auto & it : Arr)
	{
		std::string sPath = it;

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
	if (!std::experimental::filesystem::exists(path))
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
 

std::vector<std::string> CFileSystem::get_directory_iterator(const std::string & path)
{

	std::vector<std::experimental::filesystem::path> tmp = CFileSystem::directory_iterator(path);

	std::vector<std::string> ret;

	for (auto it : tmp)
	{
		ret.push_back(it.string());
	}

	return ret;
}


