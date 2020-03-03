
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
		return 1;

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

	for (auto it : HTMLArr)
	{
		IHotelParser::GetNameAndPrice(it, Seting, ResultObject, sResult);
	}
	 
	ResultObject.SaveAllName(Base::CUtil::GetDirByFilePath(HTMLArr[0]) + ALL_NAME_HOTEL_BY_ALL_FILE_IN_THIS_DIR);

	client::CFileManager::GetAllHotelName(Base::CUtil::GetDirByFilePath(HTMLArr[0]));

#endif
	return 0;
}

