#include <QCoreApplication>
#include <vector>
#include "database.h"

void Usage()
{
    printf("[Usage] : <add> <uniq_key_appart>");
    exit(0);
}


class CObject_FILE_NAME_SPY
{
public:
    static  bool CreateTable()
    {
        DataBase       database;

        CTableObject   TableColumnNames;
        TableColumnNames.SetColumnNames({"APART_NAME", "APART_COST", "APART_UNIQ_KEY"});

        CSettingDB  SettingDB;
        SettingDB.setName_table("FILE_NAME_SPY");
        SettingDB.SetDatabaseName("C:/example/FILE_NAME_AND_COST_DB.db");

        database.SetSettingDB(SettingDB);
        if ( database.ConnectToDataBase(TableColumnNames) )
        {
            database.AddToTable( TableColumnNames._Stolbic ,{"1", "2", "3"} );
        }
        return true;
    }

};

class CObject_add_apart_key
{
public:
   static  bool CreateTable()
    {
        DataBase       database;

        CTableObject   TableColumnNames;
        TableColumnNames.SetColumnNames({"APART_NAME", "APART_COST", "APART_UNIQ_KEY"});

        CSettingDB  SettingDB;
        SettingDB.setName_table("apart_key");
        SettingDB.SetDatabaseName("C:/example/uniq_apart_key.db");

        database.SetSettingDB(SettingDB);
        if ( database.ConnectToDataBase(TableColumnNames) )
        {
            database.AddToTable( TableColumnNames._Stolbic ,{"1", "2", "3"} );
        }
        return true;
    }

};

class CReques_full_raw_info_by_apart{
public:

   static bool create_table(  std::string file_db
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
        if ( database.ConnectToDataBase(TableColumnNames) )
        {
            database.AddToTable( TableColumnNames._Stolbic, TableColumnNames._Stolbic );
        }
        return true;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CReques_full_raw_info_by_apart::create_table("C:/example/full_info_raw_apart.db", "raw_apart"
    , { "APART_NAME", "APART_COST", "APART_UNIQ_KEY", "DATA_REQ", "DATA_START", "DATA_END" } );

    return a.exec();
}



