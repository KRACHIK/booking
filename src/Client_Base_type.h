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

	static int count_line_in_one_raw_object();

	int get_cost() const;

	CHome GetHome() const;
	Base::CData GetDataStart() const;
	Base::CData GetDataEnd() const;

	Base::CData get_Level2_data() const;

	std::string Serialize();


	static CHomeNameAndCostAndData Derialize(const std::string  & LineArr, const std::string  & LineArr2);


private:
	CHome _Home;
	Base::CData _Start, _End;
	Base::CData _Level2_data;
};

#endif 
