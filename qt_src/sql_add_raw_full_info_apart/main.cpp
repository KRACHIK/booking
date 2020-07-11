#include <QCoreApplication>
#include "apart_raw_info.h"
#include "../src_sql_engine/database.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CApartRawInfo ApartRawInfo;
/*
     CReques_full_raw_info_by_apart::create_table(
                "C:/example/FULL_INFO_RAW_APART.db"
                , "RAW_INFO_APART"
                , ApartRawInfo.get_colums_name()
                );
*/
    if  (argc == 8)
    {

        std::string proga_path = argv[0];
        ApartRawInfo._APART_NAME= argv[1];
        ApartRawInfo._APART_COST= argv[2];
        ApartRawInfo._APART_UNIQ_KEY= argv[3];
        ApartRawInfo._DATA_REQ= argv[4];
        ApartRawInfo._DATA_START= argv[5];
        ApartRawInfo._DATA_END= argv[6];
        ApartRawInfo._RAW_SOURCE_DIR = argv[7];

        CReques_full_raw_info_by_apart::add_sql_to_db( ApartRawInfo );
        return 0;

    }


    //return a.exec();
    return 0;
}
