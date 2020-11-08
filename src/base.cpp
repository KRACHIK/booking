
#include "base.h"
#include <string>

CToken::CToken(
	const std::string   & sTegStart
	, const std::string & sTegEnd
)
	: _sTegStart(sTegStart)
	, _sTegEnd(sTegEnd)
{

}




std::string CStringFind_impl::Find(const std::string &str, const std::string &str2, const std::string &str3)
{
	// different member versions of find in the same order as above:
	std::size_t found = str.find(str2);

	if (found != std::string::npos)
	{
		//std::cout << "first  found at: " << found << '\n';
		//std::cout << "second found at: " << found + str2.size() << '\n';

		int Start, End;

		Start = found + str2.size();

		found = str.find(str3, found + str2.size() + 1);

		if (found != std::string::npos)
		{
			//std::cout << "thrite : " << found << '\n';
			End = found;
			int Size = abs(Start - End);
			std::string sResult = str.substr(Start, Size);
			//std::cout << "[" << sResult << "]\n";
			return sResult;
		}
	}

	return "";
}

void CStringFind_impl::FindEnd(const std::string &str, const std::string &str2, int & found)
{
	// DIM
	int Start, End;
	int Result = 0;

	// каретка

	while (true)
	{
		found = str.find(str2, found + 1);

		if (found != std::string::npos)
		{
			// ok 
			Result = found;
		}
		else
		{
			found = Result;
			return;
		}
	}

}

std::string CStringFind_impl::FindForeach(const std::string &str, const std::string &str2, const std::string &str3, int & found)
{
	// DIM
	int Start, End;
	std::string sResult;

	// каретка
	found = str.find(str2, found + 1);

	if (found != std::string::npos)
	{
		// позиция за кареткой (словом)
		Start = found + str2.size();

		// второй поиск начиная ПРЕДЫДУЩЕЙ позиции каретки
		found = str.find(str3, Start + 1);

		if (found != std::string::npos)
		{
			//std::cout << "thrite : " << found << '\n';
			End = found;
			int Size = abs(Start - End);

			sResult = str.substr(Start, Size);
			//std::cout << "[" << sResult << "]\n";
			found++;
			//return sResult;
		}
		else
		{
			found = -1;
			//std::cout << "[return    // bad or end find" << "]\n";
			return ""; // bad or end find
		}

	}
	else
	{
		found = -1;
		return ""; // bad or end find
	}

	return sResult;

}


std::string CFindImpl::Read_And_Find(const std::string & sFileName, std::string str2, std::string str3)
{
	std::string line;

	std::ifstream in(sFileName); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, line))
		{

			std::string sResult = CStringFind_impl::Find(line, str2, str3);

			if (sResult.size() > 0)
			{

				//std::cout << "->[" << sResult << "]\n";
				return sResult;
			}
		}
	}
	else
	{
		std::cout << "Error Open file \n";
	}

	in.close();     // закрываем файл

	std::cout << "End" << std::endl;

	return "";
}

std::string CFindImpl::Find(const std::string & line, std::string str2, std::string str3)
{

	std::string sResult = CStringFind_impl::Find(line, str2, str3);

	if (sResult.size() > 0)
	{
		//std::cout << "->[" << sResult << "]\n";
		return sResult;
	}

	Log::CFileLog::Log("[CFindImpl::Find] : Not Find token1: " + str2 + " token2: " + str3, LOG_COMMON_ENGINE);

	return "";
}



std::vector<std::string> CFileRead::GetArrTokenRaw_NOT_MOVE_CARRETKA(const std::string & FileText, CToken Token)
{

	std::vector<std::string> Arr;
	int found = 0;
	std::string  sResult;

	while (found >= 0)
	{
		sResult = CStringFind_impl::FindForeach(FileText, Token.GetTegStart(), Token.GetTegEnd(), found);

		if (found >= 0)
		{
			found -= Token.GetTegEnd().size() - 1;

			Arr.push_back(sResult);
		}

	}

	return Arr;
}

std::vector<std::string> CFileRead::GetArrTokenRaw(const std::string & FileText, CToken Token)
{
	std::vector<std::string> Arr;
	int found = 0;
	std::string  sResult;

	while (found >= 0)
	{
		sResult = CStringFind_impl::FindForeach(FileText, Token.GetTegStart(), Token.GetTegEnd(), found);

		if (found >= 0)
		{
			std::cout << " " << sResult << " ";
			Arr.push_back(sResult);
		}

	}

	std::cout << " " << sResult << "\n";
	return Arr;
}

std::vector<int> CFileRead::GetArrToken(const std::string & FileText, CToken Token)
{
	std::vector<int> Arr;
	int found = 0;
	std::string  sResult;

	while (found >= 0)
	{
		sResult = CStringFind_impl::FindForeach(FileText, Token.GetTegStart(), Token.GetTegEnd(), found);
		  
		if (found >= 0)
		{
			Log::CFileLog::Log("[CFileRead::GetArrToken] : " + sResult, LOG_PARSER);

			Arr.push_back(std::stoi(sResult));
		}
	}


	return Arr;
}

std::string CFileRead::FindOneTokenInFile(const std::string & sFileName, CToken Tokken)
{
	std::string sResult = CFindImpl::Read_And_Find(sFileName, Tokken.GetTegStart(), Tokken.GetTegEnd());
	return sResult;
}

std::string CFileRead::FindOneTokenInText(const std::string & sFileName, CToken Tokken)
{
	std::string sResult = CFindImpl::Find(sFileName, Tokken.GetTegStart(), Tokken.GetTegEnd());
	return sResult;
}



std::vector<std::string> CFileRead::open_file(const std::string & sFileName)
{
	std::string line;
	std::vector<std::string> sResult;

	std::ifstream in(sFileName); // окрываем файл для чтения

	if (in.is_open())
	{
		while (getline(in, line))
		{
			sResult.push_back(line);
		}
	}
	else
	{
		Log::CFileLog::Log("[CFileRead::OpenFile] : Error Open file ", LOG_COMMON_ENGINE);
	}

	in.close();     // закрываем файл

	return sResult;
}

std::string CFileRead::OpenFileAndReplaceCRLF(const std::string & sFileName)
{
	std::string line;
	std::string sResult;

	line.clear();
	sResult.clear();

	std::ifstream in(sFileName); // окрываем файл для чтения

	if (in.is_open())
	{
		while (getline(in, line))
		{
			sResult += line;
		}
	}
	else
	{
		std::cout << "Error Open file \n";
	}

	in.close();     // закрываем файл

	//std::cout << "End" << sResult << std::endl;

	for (int i = 0; i < sResult.size(); i++)
	{
		if (sResult[i] == '"')
		{
			sResult[i] = '|';
		}
	}

	//std::stringstream ss;
	//ss << "Channel " << sResult;
	//
	//std::ofstream outFile(sNewFileName);
	//outFile << ss.rdbuf();
	//outFile.close();

	return sResult;
}

std::string CFileRead::ReplaceCRLF(const std::string & sText)
{
	std::string sResult = sText;

	for (int i = 0; i < sResult.size(); i++)
	{
		if (sResult[i] == '"')
		{
			sResult[i] = '|';
		}
	}
	return sResult;
}

std::string CFileRead::ReplaceSpace(std::string  s)
{
	int k = 0;
	//std::string s;

	int i = 0;
	for (i; i < s.length(); i++)
	{
		if (s[i] == ' ')
		{
			k++;
			s.erase(i, 1);
			i--;
		}
	}


	return s;
}


int CFileRead::GetPositionPosledneNaideniToken(const std::string & FileText, CToken Token)
{
	int found = 0;

	CStringFind_impl::FindEnd(FileText, Token.GetTegStart(), found);

	return found;
}

