#include <QCoreApplication>
#include "../src_sql_engine/database.h"
#include "sql_find_get_assoc_info.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CUniqKey  UniqKey;
    CUniqKeydbManager::sql_select(UniqKey);

    return 0;
}
