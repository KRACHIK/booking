#ifndef BASE_H
#define BASE_H

#include "common.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


class CToken
{
public:

	CToken(
		const std::string   & sTegStart
		, const std::string & sTegEnd
	)
		: _sTegStart(sTegStart)
		, _sTegEnd(sTegEnd)
	{

	}


	std::string GetTegStart() { return _sTegStart; }
	std::string GetTegEnd() { return _sTegEnd; }

private:
	std::string _sTegStart;
	std::string _sTegEnd;
	std::string _sData;

};


class CStringFind_impl
{
public:

	static std::string Find(const std::string &str, const std::string &str2, const std::string &str3)
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

	static std::string FindForeach(const std::string &str, const std::string &str2, const std::string &str3, int & found)
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
};

class CFindImpl
{
public:
	static std::string Read_And_Find(const std::string & sFileName, std::string str2, std::string str3)
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

	static std::string Find(const std::string & line, std::string str2, std::string str3)
	{

		std::string sResult = CStringFind_impl::Find(line, str2, str3);

		if (sResult.size() > 0)
		{
			//std::cout << "->[" << sResult << "]\n";
			return sResult;
		}
		else
		{
			std::cout << "Error Open file \n";
		}

		std::cout << "End" << std::endl;

		return "";
	}

};

class CFileRead
{
public:
	///		
	static std::vector<std::string> GetArrTokenRaw_NOT_MOVE_CARRETKA(const std::string & FileText, CToken Token)
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

	static std::vector<std::string> GetArrTokenRaw(const std::string & FileText, CToken Token)
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


	static std::vector<int> GetArrToken(const std::string & FileText, CToken Token)
	{
		std::vector<int> Arr;
		int found = 0;
		std::string  sResult;

		while (found >= 0)
		{
			sResult = CStringFind_impl::FindForeach(FileText, Token.GetTegStart(), Token.GetTegEnd(), found);

			if (found >= 0)
			{
				//Log::CFileLog::Log("[CFileRead::GetArrToken] : " + sResult, LOG_PARSER);

				Arr.push_back(std::stoi(sResult));
			}
		}

		  
		return Arr;
	}


	static std::string FindOneTokenInFile(const std::string & sFileName, CToken Tokken)
	{
		std::string sResult = CFindImpl::Read_And_Find(sFileName, Tokken.GetTegStart(), Tokken.GetTegEnd());
		return sResult;
	}

	static std::string FindOneTokenInText(const std::string & sFileName, CToken Tokken)
	{
		std::string sResult = CFindImpl::Find(sFileName, Tokken.GetTegStart(), Tokken.GetTegEnd());
		return sResult;
	}
	//

	static std::string OpenFileAndReplaceCRLF(const std::string & sFileName)
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

	static std::string ReplaceCRLF(const std::string & sText)
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



	static std::string CFileRead::ReplaceSpace(std::string  s)
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

};


#endif /*BASE_H*/