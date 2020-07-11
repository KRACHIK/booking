#ifndef APART_RAW_INFO_H
#define APART_RAW_INFO_H
#include <string>
#include <vector>
#include "../src_sql_engine/database.h"

class CUniqKey
{
public:
    std::string _DATA_BASE_FILE = "C:/example/UNIQ_KEY_APART.db";
    std::string _DATA_BASE_TABLE_NAME = "NameTable";
};



class CUniqKeydbManager
{
public:

   static bool sql_select( const CUniqKey &   UniqKey)
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

          database.Select();


       }
       return true;
   }


};

#endif // APART_RAW_INFO_H
