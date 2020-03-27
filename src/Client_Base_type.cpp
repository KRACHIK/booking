
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


CHome CHomeNameAndCostAndData::GetHome() const { return _Home; }

Base::CData CHomeNameAndCostAndData::GetDataStart() const { return _Start; }

Base::CData CHomeNameAndCostAndData::GetDataEnd() const { return _End; }

Base::CData CHomeNameAndCostAndData::get_Level2_data() const { return _Level2_data; }
