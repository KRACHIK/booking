 

#include "StringWrap.h"


std::string CStringFuncs::regex_replace(std::string Str, const std::string &sFind, const std::string &sReplace)
{
    std::regex e(sFind);
    return std::regex_replace(Str, e, sReplace);
}


int CStringFuncs::get_index_by_reverse_search_in_array(std::vector<std::string> Words, std::string Substr)
{
    for (int i = Words.size() - 1; i > 0; i--)
    {
        std::string Res1 = CStringFuncs::regex_search(Words[i], Substr);

        if (!Res1.empty())
            return i;
    }
    return -1;
}

std::string CStringFuncs::regex_search(std::string s, std::string sRegex)
{
    std::smatch m;
    std::regex e(sRegex);

    while (std::regex_search(s, m, e))
    {
        return m[0].str();
    }

    return std::string();
}

std::vector<std::string> CStringFuncs::get_all_regex_search(std::string s, const std::string &r)
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

std::string CStringFuncs::is_regex_ip(std::string s)
{
    std::smatch m;
    std::regex e("\\d+\\.\\d+\\.\\d+\\.\\d+");

    while (std::regex_search(s, m, e))
    {
        return m[0].str();
    }
    return std::string();
}

std::vector<std::string> CStringFuncs::split_into_lines(std::string Str)
{
    std::vector<std::string> result;

    std::stringstream ss(Str);
    std::string item;

    while (getline(ss, item))
        result.push_back(item);

    return result;
}

std::vector<std::string> CStringFuncs::split_Into_words(std::string Str)
{
    std::string Buf;
    std::stringstream ss(Str);
    std::vector<std::string> Tokens;

    while (ss >> Buf)
        Tokens.push_back(Buf);

    return Tokens;
}

 
bool CStringFuncs::is_find_str(const std::string &Str, const std::string &SubStr)
{
    return Str.find(SubStr) != std::string::npos;
}

 int CStringFuncs::get_pos_sub_str(const std::string &Str, const std::string &SubStr)
{
    return Str.find(SubStr);
}