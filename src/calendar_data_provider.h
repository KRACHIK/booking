#ifndef CALENDAR_DATA_PROVIDER_H
#define CALENDAR_DATA_PROVIDER_H


#include "Client_Base_type.h"



#ifdef QT_COMPILER
// zero
#else 
	#include "filesystem.h"
#endif  

 

#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <vector>
#include <regex>
#include <list>



class CHomeNameAndCostAndData;


namespace Level2
{

	class CMyString
	{
	public:
		static std::string do_replace(const std::string & in, const std::string &from, const std::string & to);
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

		std::vector<std::string> get_all_file_in_dir(const std::string & sDir, const std::string & sMask);

		bool Get_Next_Diapozon_Dir(std::string & Result);

		bool Parse_DayMotherYear_DayMotherYear(std::string Path, std::string & Result);

	private:
		std::string _sRootDir;
		std::vector<std::string> _DayArr; // path
		int _Index = 0;
	};


	class CDataProvider
	{
	public:
		static std::vector<std::string> GetAllNameHotelInCurDir(std::string sRootDir);

		/*
			GetArrHomeNameAndCostAndData
			get_array_HomeNameAndCostAndData_by_file
		*/
		static std::vector<CHomeNameAndCostAndData> get_array_HomeNameAndCostAndData_by_file(std::string sIntrestingDir);

		static void FindAsocDataByHomeName(const std::string & sRootDir, const std::string & sHotelName);


		static void get_assoc_data_by_quniq_key(std::vector<CHomeNameAndCostAndData> & Result
			, const std::string & sRootDir, const std::string & sHotelName
		);

		static std::vector<std::string>  get_all_uniq_key_fom_file(std::string sRootDir);
	};

}

#endif 