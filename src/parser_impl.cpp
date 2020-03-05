
#include "parser_impl.h"




void  CHomeArr::AddHome(CHome  Home)
{
	_Arr.push_back(Home);
}

void CHomeArr::Save(const std::string & sFileName)
{
	Log::CFileLog::Log("[CHomeArr::Save] : " + sFileName, LOG_PARSER);


	std::stringstream ss;

	for (auto it : _Arr)
		ss << it.GetSerialize();


	std::ofstream outFile(sFileName);
	outFile << ss.rdbuf();
	outFile.close();
}


void CFile::Save(const std::string & sText, const std::string & sFileSave)
{
	//std::cout << "[CFile::Save] : " << sFileSave << " size " << sText.size() << "\n";
	Log::CFileLog::Log("[CFile::Save] : " + sFileSave + " FileSize: " + std::to_string(sText.size()), LOG_PARSER);

	std::stringstream ss;
	ss << sText;

	std::ofstream outFile(sFileSave);
	outFile << ss.rdbuf();
	outFile.close();
}

void CFile::Save(std::stringstream ss, const std::string & sFileSave)
{
	std::ofstream outFile(sFileSave);
	outFile << ss.rdbuf();
	outFile.close();
}

void CSave::Save(std::string sFileSave)
{
	std::stringstream ss;

	{
		ss << "_HomeAviable ";
		for (auto it : _HomeAviable)
			ss << " " << it;
		ss << "\n";
	}


	{
		ss << "_PriceArr ";
		for (auto it : _PriceArr)
			ss << " " << it;
		ss << "\n";
	}


	{
		ss << "_HomeClosedName " << "\n";
		for (auto it : _HomeClosedName)
			ss << "Closed: " << it << "\n";
		ss << "\n";
	}

	std::ofstream outFile(sFileSave);
	outFile << ss.rdbuf();
	outFile.close();
}


void CSave::AddHomeAviable(int HomeAviable)
{
	_HomeAviable.push_back(HomeAviable);
}

void CSave::AddPriceArr(std::vector<int> PriceArr)
{
	for (auto it : PriceArr)
		_PriceArr.push_back(it);
}

void CSave::AddHomeClosedNameArr(std::vector<std::string>  HomeClosedNameArr)
{
	for (auto it : HomeClosedNameArr)
		_HomeClosedName.push_back(it);
}

void CSave::AddHomeName(std::string sName)
{
	_ArrName.push_back(sName);
}

void CSave::SaveAllName(std::string sFileSave)
{
	std::stringstream ss;

	for (auto it : _ArrName)
		ss << it << "\n";

	std::ofstream outFile(sFileSave);
	outFile << ss.rdbuf();
	outFile.close();
}

