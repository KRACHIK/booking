#include "Str.h"
 
namespace Str {

	std::vector <CStr> rENAME::Parse_Space(const std::string & buf)
	{
		std::vector<std::string>words;

		std::istringstream ist(buf);
		std::string tmp;

		while (ist >> tmp)
			words.push_back(tmp);

		return words;
	}


	std::string rENAME::do_replace(const std::string & in, const std::string &from, const std::string & to)
	{
		return std::regex_replace(in, std::regex(from), to);
	}

	dati rENAME::Parse_GetDataByPath(const std::string & Src)
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


	dati rENAME::Parse_day_mother_year(const std::string & Src)
	{
		/* input: 02.03.2020 -> size 10
		/* input: 12.3.2020  -> size 9
		/* input: 2.3.2020	 -> size 8
	*/

		if (Src.size() == 10 || Src.size() == 8 || Src.size() == 9)
		{
		}
		else
		{
			return  {};
		}

			  
		 
		std::string buf = do_replace(Src, "\\.", " ");
		 
		std::vector <CStr> ArrStr = Parse_Space(buf);

		std::vector <int> numArr;
		for (auto it : ArrStr)
			numArr.push_back(std::stoi(it));

		return numArr;
	}
}
 