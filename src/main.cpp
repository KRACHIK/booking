
#include <iostream>
#include <assert.h>


#include "common.h"
#include "parser.h"


#define DBG_DEMO 1
//#define DBG_PATH "D:\\Development\\booking\\bin2\\Debug\\db\\-2326178\\03.09.2020\\04.09.2020-11.09.2020" // old 
 #define DBG_PATH "D:\\Development\\booking\\bin2\\Debug\\db\\-2327363\\02.09.2020\\03.09.2020-04.09.2020" // new ok worc parse cost
 //#define DBG_PATH "D:\\Development\\booking\\bin2\\Debug\\db\\-2327363\\30.10.2020\\31.10.2020-01.11.2020" // new get cost not work 
 
//#define DBG_PATH "D:\\1"

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

#if DBG_DEMO 
	std::string sTarget = DBG_PATH;
	std::string sResult = "not use";
#else
	std::string sTarget = argv[1];
	std::string sResult = argv[2];
#endif

	std::string input_prams("Dir Target: <" + sTarget + ">" + " file name for save result parse: <" + sResult + ">");

	Log::CFileLog::Log(input_prams, LOG_PARSER, LOG_PARSER);

	std::vector<std::experimental::filesystem::path> Arr = CFileSystem::directory_iterator(sTarget);
	std::vector<std::string> HTMLArr = CFileSystem::Filter(Arr, ".html");

	if (HTMLArr.empty())
	{
		Log::CFileLog::Log("Eror! not find HTML" + input_prams, LOG_PARSER_ERR, LOG_PARSER);
		return 1;
	}

	CHomeArr homeArr;

	for (auto it : HTMLArr)
	{
#if 1
		IHotelParser::GetNameAndPrice(it, Seting, ResultObject, sResult, homeArr);
#else
		std::string sTotalHome = IHotelParser::GetTotalHome(it);
#endif
	}
	 
	bool bRet = homeArr.is_not_init_objects();
	if (bRet )
	{  
		Log::CFileLog::Log("[" + std::string(__func__) + " : bad parse in dir "
			+ Base::CUtil::GetDirByFilePath(HTMLArr[0])
			+ " navernoe, booking.com izminil dizain, i teper, nujnih html tegov !Ý.", LOG_PARSER, LOG_PARSER);
		assert(false);
		exit(-1);
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
 