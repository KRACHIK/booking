//#include "def.h"
//

#include "calendar_data_provider.h"
#include "DownloadModul.h"
#include "calendar_def.h"
#include "logic_impl.h"
#include "common.h"
#include "calendar.h"


#include <chrono>
#include <thread>


#define DBG_DATA_OB_ODNM_OTELE 0 
#if DBG_DATA_OB_ODNM_OTELE   

static void demo()
{
	Level2::CDataProvider::FindAsocDataByHomeName(
		/*dir */ "D:\\Development\\booking\\bin2\\Debug\\db\\-2327363\\01.03.2020\\02.03.2020-03.03.2020"
		/*uniq name*/, "SKYROOMS_https://q-cf.bstatic.com/xdata/images/hotel/square200/243733892.jpg?k=5e86d994cfe2e2325a09e89053c7ece52373406c12ed91529287096327f81cea&o=");

}
#endif

int main()
{

#if DBG_DATA_OB_ODNM_OTELE  
	demo();
#endif

	std::vector<client::CTask> ReDownloadTaskArr;
	CDownLoadList  DownLoadList;
	client::CSeting  Seting;
	std::vector<std::experimental::filesystem::path> level2dir = client::CLogic::get_all_level2_dir(DownLoadList, Seting);
	std::vector<std::experimental::filesystem::path> level3dir = client::CLogic::get_all_level3_dir(DownLoadList, level2dir, Seting);
	int i = 0;


	std::vector<CHomeNameAndCostAndData> Result;


	for (auto it : level3dir)
	{

		if (i % 7 == 0)
		{

			Log::CFileLog::Log("Task parse: " + std::to_string(i) + "/" + std::to_string(level3dir.size()) + " call ", LOG_MAIN_DATA_OB_ODNOM_OTELE);

			Level2::CDataProvider::get_assoc_data_by_quniq_key(Result, it.string(),
				"ApartmentALPINEbyAtrium,NewGudauri_https://r-cf.bstatic.com/xdata/images/hotel/square200/235025924.jpg?k=4720c6a2b75fdad1f2b1c6e171df6455148bbd44301640f893a3361b3e04b587&o="
			);
		}
		i++;
	}

	CHotelManager HotelManager;

	for (CHomeNameAndCostAndData it : Result)
	{
		HotelManager.push_back(it);
	}


	HotelManager.Compute();
	HotelManager.save_result_compute("assoc_data.txt");

	return 0;
}



