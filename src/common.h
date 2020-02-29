#ifndef   COMMON_H
#define   COMMON_H
#include "def.h"
  
namespace Base 
{
	class CData
	{
	public:
		int startDay;
		int startMonth;
		int startYear;
	};
}

namespace L2
{ 
	class CData
	{
	public:

		static std::string GetStringCurrentDaraAndOffsetDay(int ADD_DAYS)
		{
			struct tm *u;
			char s1[40] = { 0 }, s2[40] = { 0 };
			const time_t timer = time(NULL);
			u = localtime(&timer);
			strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", u);
			u->tm_mday += ADD_DAYS;
			time_t next = mktime(u);
			u = localtime(&next);
			strftime(s2, 80, "%d.%m.%Y", u);

			return  std::string(s2);
		}

		static Base::CData  GetStringCurrentDaraAndOffsetDay2(int ADD_DAYS)
		{
			struct tm *u;
			char  day[40] = { 0 }, month[40] = { 0 }, year[40] = { 0 };

			const time_t timer = time(NULL);
			u = localtime(&timer);
			u->tm_mday += ADD_DAYS;
			time_t next = mktime(u);
			u = localtime(&next);

			strftime(day, 80, "%d ", u);
			strftime(month, 80, "%m", u);
			strftime(year, 80, "%Y", u);

			Base::CData da;
			da.startDay = std::stoi(day);
			da.startMonth = std::stoi(month);
			da.startYear = std::stoi(year);

			return da;
		}

		static Base::CData GetCurData()
		{
			struct tm *u;
			char  day[40] = { 0 }, month[40] = { 0 }, year[40] = { 0 };
			const time_t timer = time(NULL);
			u = localtime(&timer);


			strftime(day, 80, "%d ", u);
			strftime(month, 80, "%m", u);
			strftime(year, 80, "%Y", u);

			Base::CData da;

			da.startDay = std::stoi(day);
			da.startMonth = std::stoi(month);
			da.startYear = std::stoi(year);

			return da;
		}

	};
}

namespace OS {
	class CSystyem
	{
	public:
		static std::string GetSlash()
		{
			//return "\\";
			return "//";
		}
	};
}

namespace client
{  
	class CSeting
	{
	public:
		CSeting()
		{
			_sWorkDir = "D://Development//booking//bin2//Debug//db";
			_sProgaDir = "D://Development//booking//bin2//Debug";
		}

		std::string GetProgaDir() const
		{
			return _sProgaDir;
		}

		int GetDay() const
		{
			return _Day;
		}

		std::string GetWorkDir() const
		{
			return _sWorkDir;
		}

		std::string GetWorkDirAndCurrentDay() const
		{
			std::string sPropDirName = GetWorkDir() + OS::CSystyem::GetSlash() + L2::CData::GetStringCurrentDaraAndOffsetDay(0);
			return sPropDirName;
		}

	private:
		std::string _sWorkDir;
		std::string _sProgaDir;

		int _Day = 3;
	};
}

#endif /* COMMON_H */
