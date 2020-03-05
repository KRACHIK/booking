
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

	CHome Home(Name, Price[0]);
	//Home.SaveBySelfName("Object_" );
	Save.AddHomeName(Name);
	homeArr.AddHome(Home);
}
 

void IHotelParser::GetNameAndPrice(std::string sFileHTML, client::CSeting Seting, CSave & Save, std::string sResult)
{
	std::string sWorkDirAndCurrentDay = Seting.GetWorkDirAndCurrentDay();

	Log::CFileLog::Log("[IHotelParser::GetNameAndPrice] : " + sFileHTML, LOG_PARSER);

	// delete  CRLF
	std::string sFileText = CFileRead::OpenFileAndReplaceCRLF(sFileHTML);

	// delete space
	sFileText = CFileRead::ReplaceSpace(sFileText);

	// DBG save
	CToken Token("<imgclass=|hotel_image|src=", "<imgclass=|hotel_image|src="); //   class="hotel_image"src="
	//CToken Token("<imgclass=|hotel_image|src=", "bui-button__text"); // bad
	std::vector <std::string> TokenArr = CFileRead::GetArrTokenRaw_NOT_MOVE_CARRETKA(sFileText, Token);
	 
	if (TokenArr.empty())
		Log::CFileLog::Log("[IHotelParser::GetNameAndPrice] : " + sFileHTML + " HE CODERJIT BLOCKOV TokenArr.empty()", LOG_PARSER_ERR);
	 
	int i = 0;
	CHomeArr homeArr;
	 
	// get pervie N-1 blockov
	for (auto Text : TokenArr)
		GetNameAndPrice_Impl(sFileHTML, Save, homeArr, Text, i++);
	  
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
		GetNameAndPrice_Impl(sFileHTML, Save, homeArr, Block, i++);
	}

	// Save Result Parse
	{
		std::string Path = Base::CUtil::GetDirByFilePath(sFileHTML, NAME_AND_COST);
		homeArr.Save(Path);
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

#if 1
	std::vector<int> Price = CFileRead::GetArrToken(sFileText, CToken("aria-hidden=|true|>BYN&nbsp;", "</div>"));
#else
	std::vector<int> Price = CFileRead::GetArrToken(sFileText, CToken("aria-hidden=|true|>US$", "</div>"));
#endif

	return Price;
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
