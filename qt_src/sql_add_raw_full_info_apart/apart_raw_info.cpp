#include "apart_raw_info.h"

CApartRawInfo::CApartRawInfo()
{

}

std::vector<std::string> CApartRawInfo::get_data_for_colums() const
{
    return {
        _APART_NAME
                ,_APART_COST
                ,_APART_UNIQ_KEY
                ,_DATA_REQ
                ,_DATA_START
                ,_DATA_END
                ,_RAW_SOURCE_DIR
    };

}

std::vector<std::string> CApartRawInfo::get_colums_name() const
{
    return {
        _TABLE_APART_NAME
                ,_TABLE_APART_COST
                ,_TABLE_APART_UNIQ_KEY
                ,_TABLE_DATA_REQ
                ,_TABLE_DATA_START
                ,_TABLE_DATA_END
                ,_TABLE_RAW_SOURCE_DIR
    };
}

bool CReques_full_raw_info_by_apart::create_table(
        std::string file_db
        , std::string table_name
        , std::vector<std::string> Colums)
{
    DataBase       database;

    CTableObject   TableColumnNames;
    TableColumnNames.SetColumnNames(Colums);

    CSettingDB  SettingDB;
    SettingDB.setName_table( table_name  );
    SettingDB.SetDatabaseName(file_db);

    database.SetSettingDB(SettingDB);

    if (
          database.OpenDataBase()
       )
    {
        bool bRet = database.CreateTable( TableColumnNames );
        return bRet;
    }
    return false;
}

bool CReques_full_raw_info_by_apart::add_sql_to_db(
        const CApartRawInfo &  ApartRawInfo
        )
{
    DataBase database;

    CTableObject  TableColumnNames;
    TableColumnNames.SetColumnNames( ApartRawInfo.get_colums_name() );

    CSettingDB  SettingDB;
    SettingDB.setName_table(  ApartRawInfo._DATA_BASE_TABLE_NAME  );
    SettingDB.SetDatabaseName(ApartRawInfo._DATA_BASE_FILE);

    database.SetSettingDB(SettingDB);
    if ( database.ConnectToDataBase(TableColumnNames) )
    {
        database.AddToTable( TableColumnNames._Stolbic, ApartRawInfo.get_data_for_colums() );
    }
    return true;
}
