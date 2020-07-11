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

#if 0
    /* Директивы имен таблицы, полей таблицы и базы данных */
    #define DATABASE_HOSTNAME   "NameDataBase"
    #define DATABASE_NAME       "Name.db"

    #define TABLE                   "NameTable"         // Название таблицы
    #define TABLE_FNAME             "FisrtName"         // Вторая колонка
    #define TABLE_SNAME             "SurName"           // Третья колонка
    #define TABLE_NIK               "Nik"               // Четвертая колонка
#else
 /*   #define DATABASE_HOSTNAME   "NameDataBase"
    #define DATABASE_NAME       "dynamik_sql.db"

    #define TABLE                   "NameTable"         // Название таблицы
    #define TABLE_FNAME             "FisrtName"             // Вторая колонка
    #define TABLE_COUNTRY           "TABLE_COUNTRY"         // Третья колонка
    #define TABLE_UNIQ_KEY_APART    "TABLE_UNIQ_KEY_APART"  // Четвертая колонка
*/
#endif
// Первая колонка содержит Autoincrement ID


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

private:

    QSqlDatabase    db;
    CSettingDB _SettingDB;
};

#endif // DATABASE_H
