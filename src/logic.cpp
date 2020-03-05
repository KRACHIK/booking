#include "def.h"

#include "logic_impl.h"
#include "common.h"
#include "DownloadModul.h"

#include <thread>
#include <chrono>


void Data1()
{
	std::time_t t = std::time(0);
	std::tm * local = std::localtime(&t);
	std::cout << "data = " << std::put_time(local, "%F") << std::endl;
	std::cout << "time = " << std::put_time(local, "%T") << std::endl;
}


void Dataa2()
{
	struct tm *u;
	char s1[40] = { 0 }, s2[40] = { 0 };
	const time_t timer = time(NULL);
	u = localtime(&timer);
	strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", u);
	printf("%s\n", s1);
#define ADD_DAYS 3
	u->tm_mday += ADD_DAYS;
	time_t next = mktime(u);
	u = localtime(&next);
	strftime(s2, 80, "%d.%m.%Y %H:%M:%S ", u);
	printf("%s\n", s2);
	getchar();
}

int main()
{
	Log::CFileLog::Log("[main]", LOG_LOGIC);

	while (true)
	{
		if (client::CLogic::IsWork())
		{
			Log::CFileLog::Log("[main] : zapusjai zadachu.", LOG_LOGIC);
			client::CLogic::Work();
		}
		else
		{
			Log::CFileLog::Log("[main] : Vse TARGET OK.", LOG_LOGIC);
		}

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



