
#include <iostream>
#include <assert.h>


#include "common.h"
#include "parser.h"

int main(int argc, const char** argv)
{
	client::CSeting Seting;
	CSave ResultObject;

#if 0
	IHotelParser::GetNameAndPrice("D:\\parse\\cur28.02.2020-see1.3.2020-3.3.2020\\booking1.html", Seting, ResultObject, "1");
	//ResultObject.Save("ResultObject.log");
#else

	if (argc != 3)
	{
		Log::CFileLog::Log("Bad Input argc, Want  \db\29.02.2020\01.03.2020-04.03.2020 FILE_NAME_FOR_SAVE_RES_WORK", LOG_PARSER_ERR);
		return 1;
	}

	std::string sTarget = argv[1];
	std::string sResult = argv[2];

	Log::CFileLog::Log("Dir Target" + sTarget, LOG_PARSER);
	Log::CFileLog::Log("parse result" + sResult, LOG_PARSER);

	std::vector<std::experimental::filesystem::path> Arr = CFileSystem::directory_iterator(sTarget);
	std::vector<std::string> HTMLArr = CFileSystem::Filter(Arr, ".html");

	if (HTMLArr.empty())
	{
		Log::CFileLog::Log("not find HTML", LOG_CALENDAR);
		return 1;
	}

	CHomeArr   homeArr;

	for (auto it : HTMLArr)
	{
#if 1
		IHotelParser::GetNameAndPrice(it, Seting, ResultObject, sResult, homeArr);
#else
		std::string sTotalHome = IHotelParser::GetTotalHome(it);
#endif
	}


	// Save Result Parse
	{
		std::string Path = Base::CUtil::GetDirByFilePath(HTMLArr[0] , NAME_AND_COST);
		homeArr.Save(Path);
		homeArr.save_apart_name_andurl(Base::CUtil::GetDirByFilePath(HTMLArr[0], FILE_UNIQ_APART_KEY));

	}

	ResultObject.SaveAllName(Base::CUtil::GetDirByFilePath(HTMLArr[0]) + ALL_NAME_HOTEL_BY_ALL_FILE_IN_THIS_DIR + FILE_FORMAT);


#endif
	return 0;
}

