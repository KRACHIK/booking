#ifndef APART_RAW_INFO_H
#define APART_RAW_INFO_H
#include <string>
#include <vector>
#include "../src_sql_engine/database.h"


class CUniqKeydbManager
{
public:

    CUniqKey GetTableSetting()
    {
        CUniqKey  UniqKey;
        UniqKey._DATA_BASE_FILE              = "C:/example/FULL_INFO_RAW_APART.db";
        UniqKey._DATA_BASE_TABLE_NAME        = "RAW_INFO_APART";
        return UniqKey;

    }

   static std::vector<CHomeNameAndCostAndData> sql_select( const CUniqKey &   UniqKey, std::string sUniq_apart_key);
};

#endif // APART_RAW_INFO_H
