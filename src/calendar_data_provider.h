#ifndef CALENDAR_DATA_PROVIDER_H
#define CALENDAR_DATA_PROVIDER_H

#include "common.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "foreach_dir.h"


#include "calendar_def.h"
#include "file.h"

#include "parser_impl.h"
#include "Client_Base_type.h"


#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>
#include <vector>


#include <regex>

 
namespace Level2
{ 
	class CMyString
	{
	public:
		static std::string do_replace(const std::string & in, const std::string &from, const std::string & to) ;
	};

	class CDataUtil
	{

	public:
		static std::vector <int> Parse_DayMotherYear_DayMotherYear(const std::string & sPredDir, const std::string & sData); 

	};

	class CIteratirDir
	{
	public:
		CIteratirDir(const std::string & sRootDir) : _sRootDir(sRootDir) { }

		void Init();
		bool Get_Next_Intresting_Iterator_Dir(std::string & Result);
		bool Parse_DayMotherYear_DayMotherYear(std::experimental::filesystem::path Path, std::string & Result);
		 
	private:
		std::string _sRootDir;
		std::vector<std::experimental::filesystem::path> _DayArr;
		int _Index = 0;
	};
	 

	class CDataProvider
	{
	public:
		static ArrHomeName GetAllNameHotelInCurDir(std::string sRootDir);
		  
		static ArrHomeNameAndCostAndData_ GetArrHomeNameAndCostAndData(std::string sIntrestingDir);  
	};

}

#endif 