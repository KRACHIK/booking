#ifndef APART_RAW_INFO_H
#define APART_RAW_INFO_H
#include <string>
#include <vector>
#include "../src_sql_engine/database.h"

class CApartRawInfo
{
public:
    CApartRawInfo();

    std::string _APART_NAME;
    std::string _APART_COST;
    std::string _APART_UNIQ_KEY;
    std::string _DATA_REQ;
    std::string _DATA_START;
    std::string _DATA_END;
    std::string _RAW_SOURCE_DIR;

    std::string _TABLE_APART_NAME = "TABLE_APART_NAME";
    std::string _TABLE_APART_COST = "TABLE_APART_COST";
    std::string _TABLE_APART_UNIQ_KEY  = "TABLE_APART_UNIQ_KEY";
    std::string _TABLE_DATA_REQ = "TABLE_DATA_REQ";
    std::string _TABLE_DATA_START = "TABLE_DATA_START";
    std::string _TABLE_DATA_END = "TABLE_DATA_END";
    std::string _TABLE_RAW_SOURCE_DIR = "TABLE_RAW_SOURCE_DIR";


    std::string _DATA_BASE_FILE = "C:/example/FULL_INFO_RAW_APART.db";
    std::string _DATA_BASE_TABLE_NAME = "RAW_INFO_APART";


    std::vector<std::string> get_data_for_colums() const;

    std::vector<std::string> get_colums_name() const;
};



class CReques_full_raw_info_by_apart{
public:

   static bool create_table(  std::string file_db
                        , std::string table_name
                        , std::vector<std::string> Colums);

   static bool add_sql_to_db( const CApartRawInfo &  ApartRawInfo);


};

#endif // APART_RAW_INFO_H
