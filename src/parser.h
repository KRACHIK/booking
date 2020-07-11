#ifndef PARSER_H
#define PARSER_H

#include "def.h"
#include "file.h"
#include "filesystem.h"

#include "base.h"

#include "parser_impl.h"

#include "common.h"

class IHotelParser
{
public:
	static void Parse(std::string sFileHTML, CSave & Save);

public:
	static void GetNameAndPrice(std::string sFileHTML, client::CSeting Seting, CSave & Save, std::string sResult,   CHomeArr & homeArr);

	static std::string GetTotalHome(std::string sFileHTML);

private:


	static std::string	get_url_IMGMini(CToken tokenFindIMG, std::string & Text);
	static int			get_price_Impl(const  std::string & Text);
	static std::string	get_name_impl(const std::string & Text);


	static std::vector<int> GetArrPrice(std::string sFileHTML);

	static std::vector<int> GetArrPriceByText(std::string sText_HTML);

	static std::vector<std::string> GetClosedHome(std::string sFileHTML);

	static void GetPosledniiBlock()
	{

	}

	/* static void GetNameAndPrice_Impl(
		std::string & sFileHTML
		, CSave & Save
		, CHomeArr & homeArr
		, std::string & Text
		, int i
	);*/

	static void create_object_name_and_cost_and_url(
		std::string & sFileHTML
		, CSave & Save
		, CHomeArr & homeArr
		, std::string & Text
		, int i
		, CToken tokenURL
	);




};


#endif  /*PARSER_H*/