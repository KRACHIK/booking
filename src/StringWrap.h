 
#ifndef STRING_PARSER_H
#define STRING_PARSER_H


#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

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

  
#endif /* STRING_PARSER_H */