#ifndef PARSER_IMPL_H
#define PARSER_IMPL_H

#include <regex>

#include "def.h"
#include "file.h"
#include "base.h"

#include "def.h"
#include "file.h"
#include "base.h"

#include  "calendar_def.h"

#include  "calendar_data_provider.h"

class CFile;
class CSave;
class CLogic;
class CHome;


namespace Str {

	class Util
	{

	public:
		static std::vector <CStr> Parse_Space(const std::string & buf)
		{
			std::vector<std::string>words;

			std::istringstream ist(buf);
			std::string tmp;

			while (ist >> tmp)
				words.push_back(tmp);

			return words;
		}


		static std::string do_replace(const std::string & in, const std::string &from, const std::string & to)
		{
			return std::regex_replace(in, std::regex(from), to);
		}

		static bool Parse_GetDataByPath(const std::string & buf, Base::CData & Start, Base::CData & End)
		{
			//input  D:\Development\booking\bin2\Debug\db\29.02.2020\01.03.2020-04.03.2020\FILE.TXT
			//target  01.03.2020 04.03.2020

			std::string PathAndSpace = do_replace(buf, "\\\\", " ");
			std::vector <CStr> Arr = Parse_Space(PathAndSpace);

			CStr DiapozonDat = Arr[Arr.size() - 1];

			return Base::CData::Parse(DiapozonDat, Start, End);
		}
	};
}


class CHome
{
public:

	CHome()
	{
	}

	CHome(const std::string & Name, int Cost)
		: _sName(Name)
		, _Cost(Cost)
	{
	}

	static CHome Deserealize(const CStr & Str)
	{
		std::vector<CStr> Arr = Str::Util::Parse_Space(Str);

		CStr Name = Arr[0];
		int Cost = std::stoi(Arr[1]);

		return  CHome(Name, Cost);
	}

	void SaveBySelfName(const std::string & Prefix)
	{
		std::string  sFileName = Prefix + _sName + "_" + std::to_string(_Cost);
		Save(sFileName);
	}

	void Save(const std::string & sFileName)
	{
		std::stringstream ss;
		ss << "Name " << _sName << "\n";
		ss << "Cost " << _Cost << "\n";

		std::ofstream outFile(sFileName);
		outFile << ss.rdbuf();
		outFile.close();
	}

	std::string GetSerialize()
	{
		std::string ss = _sName + " " + std::to_string(_Cost) + "\n";
		return ss;
	}


	std::string  GetName() const { return _sName; }
	int GetCost() const { return _Cost; }


private:
	std::string  _sName;
	int _Cost;
};

class CHomeArr
{
public:

	void  AddHome(CHome  Home)
	{
		_Arr.push_back(Home);
	}

	void Save(const std::string & sFileName)
	{
		Log::CFileLog::Log("[CHomeArr::Save] : " + sFileName, LOG_PARSER);


		std::stringstream ss;

		for (auto it : _Arr)
			ss << it.GetSerialize();


		std::ofstream outFile(sFileName);
		outFile << ss.rdbuf();
		outFile.close();
	}

private:
	std::vector<CHome> _Arr;

};

class CFile
{

public:
	static void Save(const std::string & sText, const std::string & sFileSave)
	{
		std::cout << "[CFile::Save] : " << sFileSave << " size " << sText.size() << "\n";

		std::stringstream ss;
		ss << sText;

		std::ofstream outFile(sFileSave);
		outFile << ss.rdbuf();
		outFile.close();
	}

	static void Save(std::stringstream ss, const std::string & sFileSave)
	{
		std::ofstream outFile(sFileSave);
		outFile << ss.rdbuf();
		outFile.close();
	}
};

class CSave
{

public:
	void Save(std::string sFileSave)
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


	void AddHomeAviable(int HomeAviable)
	{
		_HomeAviable.push_back(HomeAviable);
	}

	void AddPriceArr(std::vector<int> PriceArr)
	{
		for (auto it : PriceArr)
			_PriceArr.push_back(it);
	}

	void AddHomeClosedNameArr(std::vector<std::string>  HomeClosedNameArr)
	{
		for (auto it : HomeClosedNameArr)
			_HomeClosedName.push_back(it);
	}

	void AddHomeName(std::string sName)
	{
		_ArrName.push_back(sName);
	}

	void SaveAllName(std::string sFileSave)
	{
		std::stringstream ss;

		for (auto it : _ArrName)
			ss << it << "\n";

		std::ofstream outFile(sFileSave);
		outFile << ss.rdbuf();
		outFile.close();
	}

private:
	std::vector<int>	_PriceArr;
	std::vector<int>	_HomeAviable;
	std::vector<std::string> _HomeClosedName;
	std::vector<std::string> _ArrName;
};

class CLogic
{
public:
	static std::string GetWorkDir()
	{
		return "D:\\parse\\test\\28.2.2020-1.3.2020";
	}
};

#endif  /*PARSER_IMPL_H*/