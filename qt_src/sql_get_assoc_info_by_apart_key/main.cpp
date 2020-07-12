#include <QCoreApplication>
#include "../src_sql_engine/database.h"
#include "sql_find_get_assoc_info.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CUniqKey  UniqKey;

    std::vector<CHomeNameAndCostAndData>  t = CUniqKeydbManager::sql_select(UniqKey
        , "AlpinaHotel_https://r-cf.bstatic.com/xdata/images/hotel/square200/233703169.jpg?k=06b920fb70ba9014be03ba225e21277da7aef7275c3550a0394d475787d42290&o="
    );

    return 0;
}
