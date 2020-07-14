#include "Str.h"


CStr CStringFuncs::remove_kovichka_and_slash(const std::string &Str)
{
    std::string buf = do_replace(Str , "\"", "");
    std::string bufbuf = do_replace(buf , "\"", "");

    return  bufbuf;
}

std::vector <CStr> CStringFuncs::Parse_Space(const std::string & buf)
{
    std::vector<std::string>words;

    std::istringstream ist(buf);
    std::string tmp;

    while (ist >> tmp)
        words.push_back(tmp);

    return words;
}


std::string CStringFuncs::do_replace(const std::string & in, const std::string &from, const std::string & to)
{
	return std::regex_replace(in, std::regex(from), to);
}

dati CStringFuncs::Parse_GetDataByPath(const std::string & Src)
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


dati CStringFuncs::Parse_day_mother_year(const std::string & Src)
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

 

std::string CStringFuncs3::regex_replace(std::string Str, const std::string &sFind, const std::string &sReplace)
{
	std::regex e(sFind);
	return std::regex_replace(Str, e, sReplace);
}


int CStringFuncs3::get_index_by_reverse_search_in_array(std::vector<std::string> Words, std::string Substr)
{
	for (int i = Words.size() - 1; i > 0; i--)
	{
		std::string Res1 = CStringFuncs3::regex_search(Words[i], Substr);

		if (!Res1.empty())
			return i;
	}
	return -1;
}

std::string CStringFuncs3::regex_search(std::string s, std::string sRegex)
{
	std::smatch m;
	std::regex e(sRegex);

	while (std::regex_search(s, m, e))
	{
		return m[0].str();
	}

	return std::string();
}

std::vector<std::string> CStringFuncs3::get_all_regex_search(std::string s, const std::string &r)
{
	std::vector<std::string> Words;

	std::smatch m;
	std::regex e(r);

	while (std::regex_search(s, m, e))
	{
		for (auto x : m)
			Words.push_back(x);

		s = m.suffix().str();
	}

	return Words;
}

std::string CStringFuncs3::is_regex_ip(std::string s)
{
	std::smatch m;
	std::regex e("\\d+\\.\\d+\\.\\d+\\.\\d+");

	while (std::regex_search(s, m, e))
	{
		return m[0].str();
	}
	return std::string();
}

std::vector<std::string> CStringFuncs3::split_into_lines(std::string Str)
{
	std::vector<std::string> result;

	std::stringstream ss(Str);
	std::string item;

	while (getline(ss, item))
		result.push_back(item);

	return result;
}

std::vector<std::string> CStringFuncs3::split_Into_words(std::string Str)
{
	std::string Buf;
	std::stringstream ss(Str);
	std::vector<std::string> Tokens;

	while (ss >> Buf)
		Tokens.push_back(Buf);

	return Tokens;
}


bool CStringFuncs3::is_find_str(const std::string &Str, const std::string &SubStr)
{
	return Str.find(SubStr) != std::string::npos;
}

int CStringFuncs3::get_pos_sub_str(const std::string &Str, const std::string &SubStr)
{
	return Str.find(SubStr);
}



