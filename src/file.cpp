
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
 