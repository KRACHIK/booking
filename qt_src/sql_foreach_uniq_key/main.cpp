#include <QCoreApplication>
#include "../src_sql_engine/database.h"
#include "sql_foreach_uniq_key.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CUniqKey UniqKey = CUniqKeydbManager_foreach::GetDBSetting();

    std::vector<std::string> key = CUniqKeydbManager_foreach::sql_select(UniqKey);


    return 0;
}
