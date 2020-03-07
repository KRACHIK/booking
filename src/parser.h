#ifndef PARSER_H
#define PARSER_H

#include "def.h"
#include "file.h"
#include "base.h"

#include "parser_impl.h"

#include "common.h"

class IHotelParser
{
public:
	static void Parse(std::string sFileHTML, CSave & Save);

public:
	static void GetNameAndPrice(std::string sFileHTML, client::CSeting Seting, CSave & Save, std::string sResult);

	static std::string GetTotalHome(std::string sFileHTML);
private:

	static std::vector<int> GetArrPrice(std::string sFileHTML);

	static std::vector<int> GetArrPriceByText(std::string sText_HTML);

	static std::vector<std::string> GetClosedHome(std::string sFileHTML);

	static void GetPosledniiBlock()
	{

	}

	static void GetNameAndPrice_Impl(
		std::string & sFileHTML
		, CSave & Save
		, CHomeArr & homeArr
		, std::string & Text
		, int i 
	);
	 
	 

};


#endif  /*PARSER_H*/