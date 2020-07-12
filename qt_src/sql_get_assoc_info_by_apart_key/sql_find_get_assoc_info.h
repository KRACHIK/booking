#ifndef APART_RAW_INFO_H
#define APART_RAW_INFO_H
#include <string>
#include <vector>
#include "../src_sql_engine/database.h"

class CUniqKey
{
public:
    std::string _DATA_BASE_FILE = "C:/example/FULL_INFO_RAW_APART.db";
    std::string _DATA_BASE_TABLE_NAME = "RAW_INFO_APART";
};



class CUniqKeydbManager
{
public:

   static std::vector<CHomeNameAndCostAndData> sql_select( const CUniqKey &   UniqKey, std::string sUniq_apart_key);
};

#endif // APART_RAW_INFO_H
