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

	CToken(const std::string & sTegStart, const std::string & sTegEnd);

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
	static std::string Find(const std::string &str, const std::string &str2, const std::string &str3);
	static std::string FindForeach(const std::string &str, const std::string &str2, const std::string &str3, int & found);
	static void FindEnd(const std::string &str, const std::string &str2, int & found);
};


class CFindImpl
{
public:
	static std::string Read_And_Find(const std::string & sFileName, std::string str2, std::string str3);
	static std::string Find(const std::string & line, std::string str2, std::string str3);
};

class CFileRead
{
public:

	/*
	 TEXT kotori soderjit odinakovi marker, (k promery "img=") togda metod vernet vse bloki
	input 1-2-3-4
		return 1-2, 2-3, 3-4
	*/
	static std::vector<std::string> GetArrTokenRaw_NOT_MOVE_CARRETKA(const std::string & FileText, CToken Token);

	static std::vector<std::string> GetArrTokenRaw(const std::string & FileText, CToken Token);
	static std::vector<int> GetArrToken(const std::string & FileText, CToken Token);
	static std::string FindOneTokenInFile(const std::string & sFileName, CToken Tokken);
	static std::string FindOneTokenInText(const std::string & sFileName, CToken Tokken);

	static int GetPositionPosledneNaideniToken(const std::string & sText, CToken Tokken);

	static std::vector<std::string>open_file(const std::string & sFileName);
	static std::string OpenFileAndReplaceCRLF(const std::string & sFileName);
	static std::string ReplaceCRLF(const std::string & sText);
	static std::string ReplaceSpace(std::string s);
};



#endif /*BASE_H*/