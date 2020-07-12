
#include "Client_Base_type.h"

CHomeNameAndCostAndData::CHomeNameAndCostAndData(
	CHome & Home
	, Base::CData & Start
	, Base::CData & End
	, Base::CData & Level2_data
)
	: _Home(Home)
	, _Start(Start)
	, _End(End)
	, _Level2_data(Level2_data)
{
}

int CHomeNameAndCostAndData::count_line_in_one_raw_object()
{
	return 2;
}


int CHomeNameAndCostAndData::get_cost() const
{
	return GetHome().GetCost();
}

CHome CHomeNameAndCostAndData::GetHome() const { return _Home; }

Base::CData CHomeNameAndCostAndData::GetDataStart() const { return _Start; }

Base::CData CHomeNameAndCostAndData::GetDataEnd() const { return _End; }

Base::CData CHomeNameAndCostAndData::get_Level2_data() const { return _Level2_data; }

std::string CHomeNameAndCostAndData::Serialize()
{
	std::string SerializeHome = _Home.GetSerialize();
	std::string SerializeVectorDat = _Level2_data.Serialize() + " " + _Start.Serialize() + " " + _End.Serialize();
	std::string Result = SerializeHome + SerializeVectorDat;

	return Result;
}

CHomeNameAndCostAndData CHomeNameAndCostAndData::Derialize(const std::string & LineArr, const std::string & LineArr2)
{
	if (LineArr.empty() || LineArr2.empty())
	{
		assert(false);
	}

	CHome home = CHome::Deserealize(LineArr);

	std::vector<std::string> ArrData = CStringFuncs::Parse_Space(LineArr2);

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


