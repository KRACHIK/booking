#include "sql_find_get_assoc_info.h"


std::vector<CHomeNameAndCostAndData> CUniqKeydbManager::sql_select(
        const CUniqKey &UniqKey, std::string sUniq_apart_key)
{
    DataBase database;

    CTableObject  TableColumnNames;
    TableColumnNames.SetColumnNames( {"str25"} );

    CSettingDB  SettingDB;
    SettingDB.setName_table( UniqKey._DATA_BASE_TABLE_NAME  );
    SettingDB.SetDatabaseName(UniqKey._DATA_BASE_FILE);

    database.SetSettingDB(SettingDB);
    if ( database.ConnectToDataBase(TableColumnNames) )
    {
        qDebug("ok connet");

        std::vector<CHomeNameAndCostAndData> ResultFind =
        database.Select_apart(
                    sUniq_apart_key.c_str()
                    );

        return ResultFind;
    }

    return {};
}
