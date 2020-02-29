
#include <iostream>
#include "base.h"
#include <assert.h>
#include "file.h"

#include "common.h"

class CFile
{

public:
	static void Save(const std::string & sText, const std::string & sFileSave)
	{
		std::cout << "[CFile::Save] : " << sFileSave << " size " << sText.size() << "\n";

		std::stringstream ss;
		ss << sText;

		std::ofstream outFile(sFileSave);
		outFile << ss.rdbuf();
		outFile.close();
	}

	static void Save(std::stringstream ss, const std::string & sFileSave)
	{

		std::ofstream outFile(sFileSave);
		outFile << ss.rdbuf();
		outFile.close();
	}
};


class CSave
{

public:
	void Save(std::string sFileSave)
	{
		std::stringstream ss;

		{
			ss << "_HomeAviable ";
			for (auto it : _HomeAviable)
				ss << " " << it;
			ss << "\n";
		}


		{
			ss << "_PriceArr ";
			for (auto it : _PriceArr)
				ss << " " << it;
			ss << "\n";
		}


		{
			ss << "_HomeClosedName " << "\n";
			for (auto it : _HomeClosedName)
				ss << "Closed: " << it << "\n";
			ss << "\n";
		}

		std::ofstream outFile(sFileSave);
		outFile << ss.rdbuf();
		outFile.close();
	}


	void AddHomeAviable(int HomeAviable)
	{
		_HomeAviable.push_back(HomeAviable);
	}

	void AddPriceArr(std::vector<int> PriceArr)
	{
		for (auto it : PriceArr)
			_PriceArr.push_back(it);
	}

	void AddHomeClosedNameArr(std::vector<std::string>  HomeClosedNameArr)
	{
		for (auto it : HomeClosedNameArr)
			_HomeClosedName.push_back(it);
	}




private:
	std::vector<int>	_PriceArr;
	std::vector<int>	_HomeAviable;
	std::vector<std::string> _HomeClosedName;
};

class CHome {
public:
	CHome(const std::string & Name, int Cost)
		: _sName(Name)
		, _Cost(Cost)
	{

	}

	void SaveBySelfName(const std::string & Prefix)
	{
		std::string  sFileName = Prefix + _sName + "_" + std::to_string(_Cost);

		Save(sFileName);
	}


	void Save(const std::string & sFileName)
	{
		std::stringstream ss;
		ss << "Name " << _sName << "\n";
		ss << "Cost " << _Cost << "\n";

		std::ofstream outFile(sFileName);
		outFile << ss.rdbuf();
		outFile.close();
	}





	std::string GetSerialize()
	{
		std::string  ss;
		ss += "Name " + _sName += "\n";
		ss += "Cost " + std::to_string(_Cost) += "\n";

		return ss;
	}


private:
	std::string  _sName;
	int _Cost;
};

class CHomeArr
{
public:

	void  AddHome(CHome  Home)
	{
		_Arr.push_back(Home);
	}

	void Save(const std::string & sFileName)
	{
		std::stringstream ss;
		ss << "Size " << _Arr.size() << "\n";

		for (auto it : _Arr)
			ss << it.GetSerialize() << "\n";


		std::ofstream outFile(sFileName);
		outFile << ss.rdbuf();
		outFile.close();
	}

private:
	std::vector<CHome> _Arr;

};

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
	static void GetNameAndPrice(std::string sFileHTML, client::CSeting Seting, CSave & Save)
	{
		std::string sWorkDirAndCurrentDay = Seting.GetWorkDirAndCurrentDay();

		std::cout << "[IHotelParser::GetNameAndPrice] : " << sFileHTML << "\n";

		// delete  CRLF
		std::string sFileText = CFileRead::OpenFileAndReplaceCRLF(sFileHTML);

		// delete space
		sFileText = CFileRead::ReplaceSpace(sFileText);

		// DBG save

		//CFile::Save(sFileText, sWorkDirAndCurrentDay + OS::CSystyem::GetSlash() + "Not-Space-and-crlf.txt");

		// for odin big block. 
		CToken Token("<imgclass=|hotel_image|src=", "<imgclass=|hotel_image|src=");

		std::vector <std::string> TokenArr = CFileRead::GetArrTokenRaw_NOT_MOVE_CARRETKA(sFileText, Token);

		int i = 0;
		CHomeArr homeArr;

		for (auto Text : TokenArr)
		{
			std::string SubFileName = std::string(sWorkDirAndCurrentDay + OS::CSystyem::GetSlash() + "block " + std::to_string(++i) + ".txt");

			CFile::Save(Text, SubFileName);
			 
			std::vector<int> Price = GetArrPrice(SubFileName);

			if (Price.size() > 1)
			{
				// takogo bit hemojet 
				assert(false);
			}
			else if (Price.size() == 0)
			{
				//assert(false);
				Price.push_back(-1);
				// zapusti proceduru ybejdenia 4to nomer zan9t
			}

			// get hotel name 
			std::string Name = CFileRead::FindOneTokenInFile(SubFileName, CToken("=|alt=|", "|data-google-track="));

			CHome Home(Name, Price[0]);
			Home.SaveBySelfName("Home_");

			homeArr.AddHome(Home);
		}
		homeArr.Save(sWorkDirAndCurrentDay + OS::CSystyem::GetSlash() + "result.log");
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



class CLogic
{
public:
	static std::string GetWorkDir()
	{
		return "D:\\parse\\test\\28.2.2020-1.3.2020";
	}
};


int main(int argc, const char** argv)
{
#if 1
	client::CSeting Seting;

	CSave ResultObject;
	IHotelParser::GetNameAndPrice("D:\\parse\\cur28.02.2020-see1.3.2020-3.3.2020\\booking1.html", Seting, ResultObject);
	ResultObject.Save("ResultObject.log");

#else
	std::string sTarget;

	if (argc == 2)
	{
		sTarget = argv[1];
	}
	else
	{
		return 1;
	}


	std::cout << "argv: " << sTarget << "\n";

	std::vector<std::experimental::filesystem::path> Arr = CFileSystem::directory_iterator(sTarget);

	std::vector<std::string> HTMLArr = CFileSystem::Filter(Arr, ".html");

	for (auto it : HTMLArr)
	{
		CSave ResultObject;
		IHotelParser::GetNameAndPrice(it, ResultObject);
		ResultObject.Save("ResultObject.log");
}
#endif
	return 0;
}