#include "database.h"
#include <string>
#include <vector>


DataBase::DataBase(QObject *parent) : QObject(parent) { }

DataBase::~DataBase() {  }

bool DataBase::ConnectToDataBase(const CTableObject & TableObject)
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */

    if(!QFile( _SettingDB.GetDatabaseName().c_str() ).exists())
    {
        //qDebug("[DataBase::connectToDataBase] : error: data base not create."  );
        return RestoreDataBase(TableObject);
    }
    else
    {
        return OpenDataBase();
    }
}

bool DataBase::RestoreDataBase( const CTableObject & TableObject)
{
    // Если база данных открылась ...
    if(this->OpenDataBase())
    {
        // Производим восстановление базы данных
        return ( CreateTable( TableObject  ) ) ? true : false;

    } else
    {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DataBase::OpenDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(_SettingDB.GetDatabaseHostname().c_str());
    db.setDatabaseName(_SettingDB.GetDatabaseName().c_str());

    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DataBase::CloseDataBase()
{
    db.close();
}

CSettingDB DataBase::GetSettingDB() const
{
    return _SettingDB;
}

void DataBase::SetSettingDB(const CSettingDB &SettingDB)
{
    _SettingDB = SettingDB;
}


bool DataBase::CreateTable( const CTableObject & TableObject)
{
    const std::vector<std::string>   Arg = TableObject._Stolbic;

    std::string cmd = "CREATE TABLE " + _SettingDB.GetNameTable() + " (" "id INTEGER PRIMARY KEY AUTOINCREMENT, ";

    for (size_t i = 0; i < Arg.size() -1; i++)
    {
       auto Stolbic_name  = Arg[i];
       cmd.append(Stolbic_name + " VARCHAR(255)    NOT NULL,");
    }
    cmd.append( Arg[Arg.size()-1]  + " VARCHAR(255)    NOT NULL ");
    cmd.append( " )"  );

    qDebug("[creatTabl] : %s", cmd.c_str()) ;

    QSqlQuery query;

    if(!query.exec(  cmd.c_str() ))
    {
        qDebug() << "DataBase: error of create " << _SettingDB.GetNameTable().c_str();
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}





/* Метод для вставки записи в базу данных
 * */
bool  DataBase::AddToTable( const std::vector<std::string> & StolbicName
                 , const std::vector<std::string> & Value)
{
    QSqlQuery query;


    std::string cmd =  "INSERT INTO " + _SettingDB.GetNameTable() + " ( " ;

    for (size_t i=0; i< StolbicName.size()-1; i++)
    {
        cmd.append(StolbicName[i] + ", ");
    }
    cmd.append(StolbicName[StolbicName.size()-1]);
    cmd.append(  " ) " ) ;
    cmd.append(  "VALUES (" ) ;


    for (size_t i=0; i< StolbicName.size()-1; i++)
    {
        cmd.append(":" + StolbicName[i]  + ", ");
    }

    cmd.append(":" + StolbicName[StolbicName.size()-1]);
    cmd.append(  ")" ) ;
    qDebug("[addToTable] : %s", cmd.c_str() );
    query.prepare(cmd.c_str());

    for (size_t i=0; i< StolbicName.size(); i++)
    {
        query.bindValue( std::string (":" + StolbicName[i] ).c_str(),     Value[i].c_str());
    }

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " <<  _SettingDB.GetNameTable().c_str();
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

std::string CSettingDB::GetDatabaseHostname() const
{
    return _database_hostname;
}

void CSettingDB::SetDatabaseHostname(const std::string &database_hostname)
{
    _database_hostname = database_hostname;
}

std::string CSettingDB::GetNameTable() const
{
    return _Name_table;
}

void CSettingDB::setName_table(const std::string &Name_table)
{
    _Name_table = Name_table;
}

std::string CSettingDB::GetDatabaseName() const
{
    return _database_name;
}

void CSettingDB::SetDatabaseName(const std::string &database_name)
{
    _database_name = database_name;
}
