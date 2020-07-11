#include <QCoreApplication>

#include "database.h"

void Usage()
{
    printf("[Usage] : <add> <uniq_key_appart>");
    exit(0);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc == 3)
    {
        //add
        std::string DesignMaker = argv[1];

        if (DesignMaker == "add")
        {
            printf("[main] : add ");
            // Подключаемся к базе данных
            DataBase database;
            database.connectToDataBase();
            database.inserIntoTable("add_apart_key", "add_apart_key", argv[2]);
            return 0;
        }
        else
        {
            Usage();
        }

    }
    else
    {
        Usage();
    }


    return a.exec();
}
