#ifndef	CLIENT_BASE_TYPE_H
#define	CLIENT_BASE_TYPE_H

#include "def.h"
#include "parser_impl.h"
#include "fix_compilate.h"// NEW

//#include "calendar_def.h"
//#include "common.h" // bad!

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <regex>


class CHomeNameAndCostAndData
{
public:
	CHomeNameAndCostAndData() {}

	CHomeNameAndCostAndData(
		CHome & Home
		, Base::CData & Start
		, Base::CData & End
		, Base::CData & Level2_data

	);

	static int count_line_in_one_raw_object()
	{
		return 2;
	}

	CHome GetHome() const;
	Base::CData GetDataStart() const;
	Base::CData GetDataEnd() const;

	Base::CData get_Level2_data() const;

	std::string Serialize()
	{
		std::string SerializeHome = _Home.GetSerialize();
		std::string SerializeVectorDat = _Level2_data.Serialize() + " " + _Start.Serialize() + " " + _End.Serialize();
		std::string Result = SerializeHome + SerializeVectorDat;

		return Result;
	}


	static CHomeNameAndCostAndData Derialize(std::vector<std::string> LineArr)
	{
		if (LineArr.size() != 2)
		{
			assert(false);
		}

		CHome home = CHome::Deserealize(LineArr[0]);

		std::vector<std::string> ArrData = Str::rENAME::Parse_Space(LineArr[1]);

		if (ArrData.size() != 3)
		{
			assert(false);
		}



		Base::CData DataInDayRequest, Data_day_start, Data_day_end;

		if (!Base::CData::Parse(ArrData[0], DataInDayRequest))
		{
		}


		if (!Base::CData::Parse(ArrData[1], Data_day_start))
		{
		}

		if (!Base::CData::Parse(ArrData[2], Data_day_end))
		{
		}

		return CHomeNameAndCostAndData(home, Data_day_start, Data_day_end, DataInDayRequest);

	}


private:
	CHome _Home;
	Base::CData _Start, _End;
	Base::CData _Level2_data;
};

#endif 
