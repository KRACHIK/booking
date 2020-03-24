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
	CHomeNameAndCostAndData(){}

	CHomeNameAndCostAndData(
		CHome & Home
		, Base::CData & Start
		, Base::CData & End
	);

	CHome GetHome() const;
	Base::CData GetDataStart() const;
	Base::CData GetDataEnd() const;

private:
	CHome _Home;
	Base::CData _Start, _End;
};

#endif 
