#ifndef STR_H
#define STR_H

#include "calendar_def.h"
#include "def.h"
//#include "common.h" // bad!

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <regex>


namespace Str {

	class rENAME
	{

	public:
		static std::vector <CStr> Parse_Space(const std::string & buf)
		{
			std::vector<std::string>words;

			std::istringstream ist(buf);
			std::string tmp;

			while (ist >> tmp)
				words.push_back(tmp);

			return words;
		}


		static std::string do_replace(const std::string & in, const std::string &from, const std::string & to)
		{
			return std::regex_replace(in, std::regex(from), to);
		}

		static dati Parse_GetDataByPath(const std::string & Src)
		{
			/* input: 02.03.2020-03.03.2020
			*/

			if (Src.size() != 21)
				return  {};

			//Src ("02.03.2020-04.03.2020");

			std::string buf = do_replace(Src, "\\.", " ");
			buf = do_replace(buf, "-", " ");
			 
			std::vector <CStr> ArrStr = Parse_Space(buf);
			 
			std::vector <int> numArr;
			for (auto it : ArrStr)
				numArr.push_back(std::stoi(it));
			              
			return numArr;
		}
	};
}


#endif 
