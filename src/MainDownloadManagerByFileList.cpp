#include "def.h"

#include "DownloadModul.h"
#include "logic_impl.h"
#include "common.h"

#include <chrono>
#include <thread>

 

int main()
{
	for (int i=0; i<13; i++)
	{
		std::vector<client::CTask> ReDownloadTaskArr;
		CDownLoadList  DownLoadList;
		client::CSeting  Seting;

		if (client::CLogic::IsPropuskDwnFile(DownLoadList, ReDownloadTaskArr, Seting))
		{
			// do download old ;

			Log::CFileLog::Log("do dwn old", LOG_LOGIC);
			client::CLogic::RunUtilDownload(ReDownloadTaskArr, Seting);
		}
		else
		{

			if (client::CLogic::IsCurrentDirCreated(DownLoadList, Seting))
			{
				Log::CFileLog::Log("dwn ok", LOG_LOGIC);
			}
			else
			{
				Log::CFileLog::Log("dwn new", LOG_LOGIC);

				std::vector<client::CTask> TaskArr;
				client::CLogic::CreateTaskForMoreCountry(DownLoadList, TaskArr, Seting);
				client::CLogic::RunUtilDownload(TaskArr, Seting);
			}


			// download new;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}



	//bool bRunUtil = client::CLogic::RunUtilDownload(TaskArr, Seting);



	// 1 если нужно работаь
	// 2 сформировать рабочие каталоги
			// получить задание
			// получить текущую дату
			// получить дату на n дней вперед
	// 3 вызвать утилиты скачивания и парса
	// 4 ожидать задания

	return 0;
}



