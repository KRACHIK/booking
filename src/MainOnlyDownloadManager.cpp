#include "def.h"

#include "DownloadModul.h"
#include "logic_impl.h"
#include "common.h"

#include <chrono>
#include <thread>




int main()
{
	Log::CFileLog::Log("[main]", LOG_LOGIC);

	

	while (true)
	{
		std::vector<client::CTask>   TaskArr;

		/*if (client::CLogic::IsPropuskDwnFile(TaskArr))
		{
			bool bDwn = client::CLogic::DwnPropuskFile(TaskArr);
		}*/

		if (client::CLogic::IsWork(TaskArr))
		{
			Log::CFileLog::Log("[main] : zapusjai zadachu.", LOG_LOGIC);
			client::CLogic::Work();
		}
		else
		{
			Log::CFileLog::Log("[main] : Vse TARGET OK.", LOG_LOGIC);
		}

		TaskArr.clear();

		std::this_thread::sleep_for(std::chrono::seconds(160));
	}

	// 1 если нужно работаь
	// 2 сформировать рабочие каталоги
			// получить задание
			// получить текущую дату
			// получить дату на n дней вперед
	// 3 вызвать утилиты скачивания и парса
	// 4 ожидать задания

	return 0;
}



