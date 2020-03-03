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
	static void Parse(std::string sFileHTML, CSave & Save)
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

private:

public:
	static void GetNameAndPrice(std::string sFileHTML, client::CSeting Seting, CSave & Save, std::string sResult)
	{
		std::string sWorkDirAndCurrentDay = Seting.GetWorkDirAndCurrentDay();

		Log::CFileLog::Log("[IHotelParser::GetNameAndPrice] : " + sFileHTML, LOG_PARSER);

		// delete  CRLF
		std::string sFileText = CFileRead::OpenFileAndReplaceCRLF(sFileHTML);

		// delete space
		sFileText = CFileRead::ReplaceSpace(sFileText);
		 
		// DBG save
		CToken Token("<imgclass=|hotel_image|src=", "bui-button__text");

		//
		std::vector <std::string> TokenArr = CFileRead::GetArrTokenRaw_NOT_MOVE_CARRETKA(sFileText, Token);

		int i = 0;
		CHomeArr homeArr;

		for (auto Text : TokenArr)
		{

#if DBG_PARSER_LOG
			std::string SubFileName = std::string(sWorkDirAndCurrentDay + OS::CSystyem::GetSlash() + "block " + std::to_string(++i) + ".txt");
			CFile::Save(Text, SubFileName);
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
		  
		std::string Path = Base::CUtil::GetDirByFilePath(sFileHTML, NAME_AND_COST);

		homeArr.Save(Path);
	}

private:
	static std::string GetTotalHome(std::string sFileHTML)
	{
		std::string sResult = CFileRead::FindOneTokenInFile(sFileHTML, CToken("availableHotels: '", "',"));
		std::cout << "[IHotelParser::GetTotalHome] sResult: " << sResult << "\n";
		return sResult;
	}

	static std::vector<int> GetArrPrice(std::string sFileHTML)
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

	static std::vector<int> GetArrPriceByText(std::string sText_HTML)
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

	static std::vector<std::string> GetClosedHome(std::string sFileHTML)
	{
		std::string sFileText = CFileRead::OpenFileAndReplaceCRLF(sFileHTML);

		sFileText = CFileRead::ReplaceSpace(sFileText);

		CFile::Save(sFileText, "Not-Space-" + sFileHTML);

		std::vector<std::string> HomeClosedNameArr = CFileRead::GetArrTokenRaw(sFileText
			, CToken("<spanclass=|sr-hotel__name|data-et-click=||>", "</span>")
		);

		return HomeClosedNameArr;
	}
};

#endif  /*PARSER_H*/