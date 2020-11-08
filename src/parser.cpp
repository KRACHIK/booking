
#include "parser.h"

void IHotelParser::Parse(std::string sFileHTML, CSave & Save)
{
	std::cout << "[IHotelParser::Parse] Start: " << sFileHTML << "\n";

	std::string TotalHome = GetTotalHome(sFileHTML);
	std::vector<int> Price = GetArrPrice(sFileHTML);

	std::vector<std::string> homeclosednamearr = GetClosedHome(sFileHTML);

	Save.AddHomeAviable(std::stoi(TotalHome));
	Save.AddPriceArr(Price);
	Save.AddHomeClosedNameArr(homeclosednamearr);

	std::cout << "[IHotelParser::Parse] End: " << sFileHTML << "\n";
}



std::string IHotelParser::get_url_IMGMini(CToken tokenFindIMG, std::string & Text)
{
	// get hotel name 
	std::string sIMG_url = CFileRead::FindOneTokenInText(Text, tokenFindIMG);
	return sIMG_url;
}




std::string IHotelParser::get_name_impl(const std::string & Text)
{
	// get hotel name 
	std::string Name = CFileRead::FindOneTokenInText(Text, CToken("=|alt=|", "|data-google-track="));
	return Name;
}




int IHotelParser::get_price_Impl(const  std::string & Text)
{
	std::vector<int> Price = GetArrPriceByText(Text);

	if (Price.size() > 1)
	{
		// takogo bit nemojet 
		assert(false);
	}
	else if (Price.size() == 0)
	{
		//assert(false);
		Price.push_back(-1);
		// zapusti proceduru ybejdenia 4to nomer zan9t
	}

	return 	Price[0];
}




void IHotelParser::create_object_name_and_cost_and_url(
	std::string & sFileHTML
	, CSave & Save
	, CHomeArr & homeArr
	, std::string & Text
	, int i
	, CToken tokenURL
)
{

	std::string sName = get_name_impl(Text);
	  
	int price = get_price_Impl(Text);
	std::string url = get_url_IMGMini(tokenURL, Text);

	CHome Home(sName, url, price);
 
	homeArr.AddHome(Home);
	Save.AddHomeName(sName);
}

/* 
void IHotelParser::GetNameAndPrice_Impl(
	std::string & sFileHTML
	, CSave & Save
	, CHomeArr & homeArr
	, std::string & Text
	, int i)
{
#if DBG_PARSER_LOG
	std::string SubFileName(FILE_DBG "_block" + std::to_string(i) + FILE_FORMAT);
	std::string Path = Base::CUtil::GetDirByFilePath(sFileHTML, SubFileName);
	CFile::Save(Text, Path);
#endif 

	std::vector<int> Price = GetArrPriceByText(Text);

	if (Price.size() > 1)
	{
		// takogo bit nemojet 
		assert(false);
	}
	else if (Price.size() == 0)
	{
		//assert(false);
		Price.push_back(-1);
		// zapusti proceduru ybejdenia 4to nomer zan9t
	}

	// get hotel name 
	std::string Name = CFileRead::FindOneTokenInText(Text, CToken("=|alt=|", "|data-google-track="));

	//

	std::string url = get_url_IMGMini(CToken("<imgclass=|hotel_image|src=|", "|data-highres=|"), sFileHTML, Save, homeArr, Text, i);


	//Home.SaveBySelfName("Object_" );
	Save.AddHomeName(Name);
	homeArr.AddHome(Home);
}
*/


void IHotelParser::GetNameAndPrice(std::string sFileHTML, client::CSeting Seting, CSave & Save, std::string sResult, CHomeArr & homeArr )
{
	Log::CFileLog::Log("[" + std::string(__func__) + "] : " + sFileHTML, LOG_PARSER, LOG_PARSER);
 
	// delete  CRLF
	std::string sFileText = CFileRead::OpenFileAndReplaceCRLF(sFileHTML);

	// delete space
	sFileText = CFileRead::ReplaceSpace(sFileText);
	 
	CFile::Save(sFileText,   "Not-Space.log"); // создает запись типа booking_not_space. потом где в другой фенку происходит вызов get_dir_iterator по маске booking.  и мы полуычаем бескоенчную екурсию 

	// DBG save
	CToken Token("<imgclass=|hotel_image|src=", "<imgclass=|hotel_image|src="); //   class="hotel_image"src="
	//CToken Token("<imgclass=|hotel_image|src=", "bui-button__text"); // bad
	std::vector <std::string> TokenArr = CFileRead::GetArrTokenRaw_NOT_MOVE_CARRETKA(sFileText, Token);


	if (TokenArr.empty())
	{
		Log::CFileLog::Log("[IHotelParser::GetNameAndPrice] : " + sFileHTML + " HE CODERJIT BLOCKOV TokenArr.empty() or block vsego odin. Error faith Ahtung ", LOG_PARSER_ERR, LOG_PARSER);
		return;
	}

	int i = 0;

	 
	// get pervie N-1 blockov
	for (auto Text : TokenArr)
	{
		create_object_name_and_cost_and_url(sFileHTML, Save, homeArr, Text, i++, CToken("|", "|data-highres=|"));
	}

	  
	{ 
		// get posledniq block number N
		// Get POsledni naideni block
		int Pos = CFileRead::GetPositionPosledneNaideniToken(sFileText, Token);
		int SizeAverageBlock = 0;
		for (auto Text : TokenArr)
			SizeAverageBlock += Text.size();
		SizeAverageBlock /= TokenArr.size();

		int TextStart = Pos;
		int TextEnd = Pos + SizeAverageBlock;

		if (TextEnd > sFileText.size())
			TextEnd = sFileText.size() - 1;

		std::string Block(sFileText, TextStart, sFileText.size());
		//GetNameAndPrice_Impl(sFileHTML, Save, homeArr, Block, i++);

		create_object_name_and_cost_and_url(sFileHTML, Save, homeArr, Block, i++ , CToken("<imgclass=|hotel_image|src=|", "|data-highres=|"));
	}

}


std::string IHotelParser::GetTotalHome(std::string sFileHTML)
{
	std::string sResult = CFileRead::FindOneTokenInFile(sFileHTML, CToken("availableHotels: '", "',"));
	std::cout << "[IHotelParser::GetTotalHome] sResult: " << sResult << "\n";
	return sResult;
}

std::vector<int> IHotelParser::GetArrPrice(std::string sFileHTML)
{
	std::string sFileText = CFileRead::OpenFileAndReplaceCRLF(sFileHTML);

	sFileText = CFileRead::ReplaceSpace(sFileText);

	CFile::Save(sFileText, sFileHTML + "Not-Space.log");

#if 1
	std::vector<int> Price = CFileRead::GetArrToken(sFileText, CToken("aria-hidden=|true|>BYN&nbsp;", "</div>"));
#else
	std::vector<int> Price = CFileRead::GetArrToken(sFileText, CToken("aria-hidden=|true|>US$", "</div>"));
#endif
	return Price;
}

std::vector<int> IHotelParser::GetArrPriceByText(std::string sText_HTML)
{
	std::string sFileText = CFileRead::ReplaceCRLF(sText_HTML);
	sFileText = CFileRead::ReplaceSpace(sFileText);
	  
	auto Parse_v1_2020_mart = [=] () -> std::vector<int> 
	{
		std::vector<int> Price = CFileRead::GetArrToken(sFileText, CToken("aria-hidden=|true|>BYN&nbsp;", "</div>")); // etot kod rabotal vmate 2020 goda. potom buking smenil dizain. i vse slomalos
		return Price;
	};

	auto Parse_v1_2020_sent9br = [=] () -> std::vector<int>
	{
		/*  input: sFileText =  "...mouseenter=|customGoal:AdeKbCcBUfQUaSHbZFVXOJUNQKFcFXZYCaJFSSZRe:2|>BYN 623</div><spanclass=|bui-u-sr-only|>ЦенаBYN 623</span></div></div><divclass=|prco-...."
			output: StrPrice  = "В 623"          */
		std::vector<std::string> StrPrice = CFileRead::GetArrTokenRaw(sFileText, CToken(":2|>BYN", "</div><spanclass=|bui-u-sr-only"));  // etot kod rabotaet He sovsev korectno (smotri input\output), 

		if (StrPrice.size() == 1)
		{
			std::vector<int> PriceInt;
			std::string ret = std::string(StrPrice[0], 2, StrPrice[0].size());
			Log::CFileLog::Log("[" + std::string(__func__) +  "std::stoi for: " + ret + " " , LOG_PARSER, LOG_PARSER);
			PriceInt.push_back(std::stoi(ret));
			return PriceInt;
		}
		return {  };
	};

	auto Parse_v1_2020_no9br = [=]() -> std::vector<int>
	{
		/*  input: sFileText =  "...mouseenter=|customGoal:AdeKbCcBUfQUaSHbZFVXOJUNQKFcFXZYCaJFSSZRe:2|>BYN 623</div><spanclass=|bui-u-sr-only|>ЦенаBYN 623</span></div></div><divclass=|prco-...."
			output: StrPrice  = "В 623"          */
		std::vector<std::string> StrPrice = CFileRead::GetArrTokenRaw(sFileText, CToken("|>BYN", "</div><spanclass=|bui-u-sr-only"));  // etot kod rabotaet He sovsev korectno (smotri input\output), 

		if (StrPrice.size() == 1)
		{
			std::vector<int> PriceInt;
			std::string ret = std::string(StrPrice[0], 2, StrPrice[0].size());
			Log::CFileLog::Log("[" + std::string(__func__) + "std::stoi for: " + ret + " ", LOG_PARSER, LOG_PARSER);
			PriceInt.push_back(std::stoi(ret));
			return PriceInt;
		}
		return {  };
	};


	std::vector<int> Price_1 = Parse_v1_2020_mart();
	std::vector<int> Price_2 = Parse_v1_2020_sent9br();
	std::vector<int> Price_3 = Parse_v1_2020_no9br();
	 
	std::vector<int> PriceResult;
	 
	int CheckParser = 0;

	if (Price_1.size() == 1)
	{
		CheckParser++;
		PriceResult = Price_1;
	}
	if (Price_2.size() == 1)
	{
		PriceResult = Price_2;
		CheckParser++;
	}
	if (Price_3.size() == 1)
	{
		PriceResult = Price_3;
		CheckParser++;
	}
	 
	if (CheckParser > 1)
	{
		Log::CFileLog::Log("[" + std::string(__func__) + "] : Error. Ahtung! [if (Price_1.size() >= 1 && Price_2.size() >= 1)] pri parsinge stranici bili obnarujeni html tegi, iz ranih vremen. ", LOG_PARSER, LOG_PARSER);		 
	}


	#if 0 
		std::vector<int> Price = CFileRead::GetArrToken(sFileText, CToken("aria-hidden=|true|>US$", "</div>"));
	#endif

	return PriceResult;
}

std::vector<std::string> IHotelParser::GetClosedHome(std::string sFileHTML)
{
	std::string sFileText = CFileRead::OpenFileAndReplaceCRLF(sFileHTML);

	sFileText = CFileRead::ReplaceSpace(sFileText);

	CFile::Save(sFileText, "Not-Space-" + sFileHTML);

	std::vector<std::string> HomeClosedNameArr = CFileRead::GetArrTokenRaw(sFileText
		, CToken("<spanclass=|sr-hotel__name|data-et-click=||>", "</span>")
	);

	return HomeClosedNameArr;
}
