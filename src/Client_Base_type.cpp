
#include "Client_Base_type.h"
 
	CHomeNameAndCostAndData::CHomeNameAndCostAndData(
		 CHome & Home
		,  Base::CData & Start
		,  Base::CData & End)
		: _Home(Home)
		, _Start(Start)
		, _End(End)
	{
	}

	CHome CHomeNameAndCostAndData::GetHome() const { return _Home; }

	Base::CData CHomeNameAndCostAndData::GetDataStart() const { return _Start; }

	Base::CData CHomeNameAndCostAndData::GetDataEnd() const { return _End; }
	 
 