#include "qt_create_calandar.h"





void compute(  CUniqKey  UniqKey, std::string apartKey )
{
    std::vector<CHomeNameAndCostAndData> Aparts =  CUniqKeydbManager::sql_select(UniqKey, apartKey );

    if ( Aparts.empty())
    {
        Log::CFileLog::Log("[compute] : not find raw info for: " + apartKey  , LOG_CALENDAR_ERR);
        return;
    }

    CHotelManager  HotelManager;

    for(CHomeNameAndCostAndData it : Aparts)
    {
        HotelManager.push_back(it);
    }
    HotelManager.Compute();

    Log::CFileLog::Log(HotelManager.get_result_for_excel(apartKey), "pol-goda.log");


    //HotelManager.save_result_compute("del-test.txt");

}
void CGetApart::init()
{
#if 1
    //get all uniq key
    CUniqKey UniqKey1 = CUniqKeydbManager_foreach::GetDBSetting();
    std::vector<std::string> Keys = CUniqKeydbManager_foreach::sql_select(UniqKey1);

    //------------------------

    for(std::string it :  Keys )
    {
        CUniqKeydbManager f;
        CUniqKey  UniqKey = f.GetTableSetting();
        compute(UniqKey, it);
    }
#else //DEMO
    CUniqKeydbManager f;
    CUniqKey  UniqKey = f.GetTableSetting();
    compute(UniqKey,
            "AlpinaHotel_https://r-cf.bstatic.com/xdata/images/hotel/square200/233703169.jpg?k=06b920fb70ba9014be03ba225e21277da7aef7275c3550a0394d475787d42290&o=" );
#endif
}

/*


compute(UniqKey,  "AlpinaHotel_https://r-cf.bstatic.com/xdata/images/hotel/square200/233703169.jpg?k=06b920fb70ba9014be03ba225e21277da7aef7275c3550a0394d475787d42290&o=" );
     compute(UniqKey,  "GudauriDacha-Too_https://q-cf.bstatic.com/xdata/images/hotel/square200/185517141.jpg?k=9793411cfb58722e774d855e4ac3cb1b0c917fcdc5da1e2bdea0224bc3250e2e&o=");
     compute(UniqKey,  "swanski_https://r-cf.bstatic.com/xdata/images/hotel/square200/234002139.jpg?k=d4113c8d60375919efb57fb3e2059275f59dd9a7d445f380c48c6b8a3cdf5089&o=" );
     compute(UniqKey,  "Mziuri_https://r-cf.bstatic.com/xdata/images/hotel/square200/184748521.jpg?k=b515e5a7df20ba2afe928b5bac9f29d3cc69d3aabcac3f82b8da5426511597da&o=" );

*/
