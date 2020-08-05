#include "sql_foreach_uniq_key.h"


CUniqKey CUniqKeydbManager_foreach::GetDBSetting()
{
    CUniqKey  UniqKey;
    UniqKey._DATA_BASE_FILE = "C:/example/UNIQ_KEY_APART.db";
    UniqKey._DATA_BASE_TABLE_NAME = "NameTable";
    return UniqKey;
}

std::vector<std::string> CUniqKeydbManager_foreach::sql_select(const CUniqKey &UniqKey)
{
    DataBase database;

    CTableObject  TableColumnNames;
    TableColumnNames.SetColumnNames( {"FirstName", "TABLE_COUNTRY", "TABLE_UNIQ_KEY_APART"} );

    CSettingDB  SettingDB;
    SettingDB.setName_table( UniqKey._DATA_BASE_TABLE_NAME  );
    SettingDB.SetDatabaseName(UniqKey._DATA_BASE_FILE);

    database.SetSettingDB(SettingDB);
    if ( database.ConnectToDataBase(TableColumnNames) )
    {
        qDebug("ok connet");
        // ok connect


        std::vector<std::string> key = database.Select();

        return key;
    }

    return {};
}
