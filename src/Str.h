#ifndef STR_H
#define STR_H

#include "calendar_def.h"

#ifdef QT_COMPILER
// zero
#else
#include "def.h"
#endif


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <regex>
 

#include <algorithm> 
#include <iterator> 

class CStringFuncs3
{
public:
	static int get_index_by_reverse_search_in_array(std::vector<std::string> Words, std::string Substr);

	static std::string regex_replace(std::string Str, const std::string &sFind, const std::string &sReplace);

	static std::vector<std::string> get_all_regex_search(std::string s, const std::string &r);
	static std::string regex_search(std::string Str, std::string sRegex);
	static std::string is_regex_ip(std::string Str);
	static bool is_find_str(const std::string &Str, const std::string &SubStr);
	static int get_pos_sub_str(const std::string &Str, const std::string &SubStr);

	static std::vector<std::string> split_into_lines(std::string Str);
	static std::vector<std::string> split_Into_words(std::string Str);
};


class CStringFuncs
{
public:

    static CStr remove_kovichka_and_slash(const std::string & Str)
    {
        std::string buf = do_replace(Str , "\"", "");
         std::string bufbuf = do_replace(buf , "\"", "");

        return  bufbuf;
    }

	static std::vector <CStr> Parse_Space(const std::string & buf);

	static std::string do_replace(const std::string & in, const std::string &from, const std::string & to);

	static dati Parse_GetDataByPath(const std::string & Src);

	static dati Parse_day_mother_year(const std::string & Src);
};


#endif 
