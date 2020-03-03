#ifndef	CLIENT_BASE_TYPE_H
#define	CLIENT_BASE_TYPE_H

#include "calendar_def.h"
#include "def.h"
//#include "common.h" // bad!

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <regex>

#include "parser_impl.h"

class  CHome;  

class CHomeNameAndCostAndData
{
public:
	CHomeNameAndCostAndData(
		const CHome & Home
		, const Base::CData & Start
		, const Base::CData & End)
		: _Home(Home)
		, _Start(Start)
		, _End(End)
	{
	}

	CHome GetHome() const { return _Home; }

	Base::CData GetDataStart() const { return _Start; }

	Base::CData GetDataEnd() const { return _End; }

private:
	CHome _Home;
	Base::CData _Start, _End;
};


#endif 
