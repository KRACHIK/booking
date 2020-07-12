#include "qt_create_calandar.h"



void CGetApart::init()
{

    //"AlpinaHotel_https://r-cf.bstatic.com/xdata/images/hotel/square200/233703169.jpg?k=06b920fb70ba9014be03ba225e21277da7aef7275c3550a0394d475787d42290&o="
    CUniqKey  UniqKey;

    std::vector<CHomeNameAndCostAndData> Aparts =  CUniqKeydbManager::sql_select(UniqKey,
      "GudauriDacha-Too_https://q-cf.bstatic.com/xdata/images/hotel/square200/185517141.jpg?k=9793411cfb58722e774d855e4ac3cb1b0c917fcdc5da1e2bdea0224bc3250e2e&o="
                                                                                 );

    CHotelManager  HotelManager;

    for(CHomeNameAndCostAndData it : Aparts)
    {
        HotelManager.push_back(it);
    }
    HotelManager.Compute();

    HotelManager.save_result_compute("del-test.txt");

}
