#include <QCoreApplication>
#include "../src_sql_engine/database.h"
#include "qt_create_calandar.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CGetApart::init();

    return 0;
}
