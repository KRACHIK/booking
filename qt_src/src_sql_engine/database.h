#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#include "../../Src/Client_Base_type.h"
#include "../../Src/Str.h"

class CUniqKey
{
public:
    std::string _DATA_BASE_FILE = "C:/example/FULL_INFO_RAW_APART.db";
    std::string _DATA_BASE_TABLE_NAME = "RAW_INFO_APART";
};

class CSettingDB
{
public:
    void SetDatabaseHostname(const std::string &GetDatabaseHostname);
    void SetDatabaseName(const std::string &GetDatabaseName);
    void setName_table(const std::string &GetNameTable);

    std::string GetDatabaseHostname() const;
    std::string GetDatabaseName() const;
    std::string GetNameTable() const;

private:
    std::string _Name_table = "_Name_table";
    std::string _database_hostname = "NameDataBase";
    std::string _database_name = "C:/example/database_name.db";
};


class CTableObject
{
public:
    void SetColumnNames(std::vector<std::string> ColumnNames )
    {
        _Stolbic = ColumnNames;
    }

    std::vector<std::string> _Stolbic = {"APART_NAME", "COST", "UNIQ_KEY"};
};

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

    bool CreateTable( const CTableObject & TableObject );
    bool ConnectToDataBase(const CTableObject & TableObject);
    bool RestoreDataBase(const CTableObject & TableObject );     // Восстановление базы данных
    bool AddToTable( const std::vector<std::string> & StolbicName , const std::vector<std::string> & Value);

    bool OpenDataBase();        // Открытие базы данных
    void CloseDataBase();       // Закрытие базы данных
    CSettingDB GetSettingDB() const;
    void SetSettingDB(const CSettingDB &GetSettingDB);


    std::vector<std::string> Select();

    std::vector<CHomeNameAndCostAndData> Select_apart(std::string UniqApartKey);

private:

    QSqlDatabase    db;
    CSettingDB _SettingDB;
};

#endif // DATABASE_H
