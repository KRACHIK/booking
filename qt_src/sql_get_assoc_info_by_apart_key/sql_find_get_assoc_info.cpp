#include "sql_find_get_assoc_info.h"


bool CUniqKeydbManager::sql_select(const CUniqKey &UniqKey)
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
        // ok connect

        database.Select_apart(
                    "AlpinaHotel_https://r-cf.bstatic.com/xdata/images/hotel/square200/233703169.jpg?k=06b920fb70ba9014be03ba225e21277da7aef7275c3550a0394d475787d42290&o="
                    );


    }
    return true;
}
