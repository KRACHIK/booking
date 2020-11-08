#ifndef PARSER_IMPL_H
#define PARSER_IMPL_H

#include <regex>

#include "def.h"

#ifdef QT_COMPILER
	// zero
#else
	#include "file.h"
	#include "filesystem.h"
#endif  

#include "base.h"
#include "apartament.h"
#include  "calendar_def.h"
#include  "calendar_data_provider.h"


class CHomeArr
{
public:

	void AddHome(CHome  Home);

	void Save(const std::string & sFileName);

	void save_apart_name_andurl(const std::string & sFileName);

	bool is_not_init_objects() const 
	{
		if (_Arr.empty())
		{
			return true;
		}

		auto is_not_init_cost = [=]() {
			int SumCost = 0;
			for (auto it : _Arr)
			{
				SumCost += it.GetCost();
			}

			if (SumCost <= 0)
			{
				return true;
			}

			return false;
		};

		return is_not_init_cost();
	}

private:
	std::vector<CHome> _Arr;
};

class CFile
{

public:
	static void Save(const std::string & sText, const std::string & sFileSave);

	static void Save(std::stringstream ss, const std::string & sFileSave);
};



class CSave
{
public:
	void Save(std::string sFileSave);
	void AddHomeAviable(int HomeAviable);
	void AddPriceArr(std::vector<int> PriceArr);
	void AddHomeClosedNameArr(std::vector<std::string>  HomeClosedNameArr);
	void AddHomeName(std::string sName);
	void SaveAllName(std::string sFileSave);


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