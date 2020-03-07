
#include <iostream>
#include <assert.h>


#include "common.h"
#include "parser.h"
#include "file.h"

#include "calendar_data_provider.h"


class CIteratorForTotalHome
{
public:
	static void ParseTotalHome(const std::string &sRoot, const std::string & sMask)
	{

	}

private:

};

class CTottalHome
{
public:
	CTottalHome(std::string  sDir_diapozon, int  total_home)
		: _sDirDiapozon(sDir_diapozon)
		, _totalHome(total_home)
	{
	}



public:
	std::string _sDirDiapozon;
	int _totalHome;
};

int main(int argc, const char** argv)
{
	client::CSeting Seting;


	std::string sTarget = "D:\\Development\\booking\\bin2\\Debug\\db\\All-db-06.03.2020-1Year";//argv[1];
	Level2::CIteratirDir it(sTarget);
	it.Init();
	std::string sDirDiapozon;

	std::vector<CTottalHome > ResultTotalHome365Day;

	// Get_Next_Diapozon_Dir pereberet vse "01.01.2021-08.01.2021" "02.01.2021-09.01.2021" ...

	while (it.Get_Next_Diapozon_Dir(sDirDiapozon))
	{

		std::string sdata_diapozon_for_excel;

		{
			Base::CData Start, End;
			std::vector <int> DataArr = Level2::CDataUtil::Parse_DayMotherYear_DayMotherYear(sTarget, sDirDiapozon);
			 Base::CData::create_data_by_vector_int(DataArr, Start, End);
			 sdata_diapozon_for_excel = Base::CData::get_str_for_excel(Start, End);
		}


		// All file in HTML in  01.01.2021-08.01.2021 
		std::vector<std::string> HTML_Arr = it.get_all_file_in_dir(sDirDiapozon, ".html");

		if (HTML_Arr.empty())
		{
			Log::CFileLog::Log("GetTotalHome : HTML_Arr emty ", LOG_TOTAL_HOME_PARSER_ERR);
			continue;
		}


		// DBG PRINT
		Log::CFileLog::Log("count file in Next Diapozon = " + std::to_string(HTML_Arr.size()), LOG_TOTAL_HOME_PARSER);

		std::vector<std::string> ArrTotalHomeStr;

		for (auto it : HTML_Arr)
		{
			std::string sTotalHome = IHotelParser::GetTotalHome(it);

			if (sTotalHome.empty())
			{
				Log::CFileLog::Log("GetTotalHome : IHotelParser::GetTotalHome result parse 0. not find  ", LOG_TOTAL_HOME_PARSER_ERR);
				continue;
			}
			ArrTotalHomeStr.push_back(sTotalHome);
			break;
		}

		if (ArrTotalHomeStr.empty())
		{
			Log::CFileLog::Log("GetTotalHome : IHotelParser::GetTotalHome result parse 0. not find  or not dwn file html", LOG_TOTAL_HOME_PARSER_ERR);
		}
		else
		{
			std::vector<int> ArrTotalHome;

			for (std::string it : ArrTotalHomeStr)
			{
				ArrTotalHome.push_back(std::stoi(it));
			}

			// filter data
			for (int it : ArrTotalHome)
			{
				if (it != ArrTotalHome[0])
				{
					assert(false);
					Log::CFileLog::Log("GetTotalHome : raznie rezultati poiska in dir " + sDirDiapozon + " a doljni bit odno i toje kol-vo oteley", LOG_TOTAL_HOME_PARSER_ERR);
				}
			}
			ResultTotalHome365Day.push_back(CTottalHome(sdata_diapozon_for_excel, ArrTotalHome[0]));
		}

	}

	for (auto it : ResultTotalHome365Day)
	{ 
		Log::CFileLog::Log(it._sDirDiapozon + " " + std::to_string(it._totalHome), LOG_TOTAL_HOME_PARSER);
	}


	return 0;
}

