#ifndef APART_RAW_INFO_UniqKeydbManager_foreach_H
#define APART_RAW_INFO_UniqKeydbManager_foreach_H
#include <string>
#include <vector>
#include "../src_sql_engine/database.h"


class CUniqKeydbManager_foreach
{
public:

    static  CUniqKey GetDBSetting();

    static std::vector<std::string> sql_select( const CUniqKey &   UniqKey);

};

#endif // APART_RAW_INFO_H
