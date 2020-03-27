#ifndef CALENDAR_MAP_ADAPTER
#define CALENDAR_MAP_ADAPTER

#include "common.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "foreach_dir.h"
#include "calendar_data_provider.h"


#include "calendar_def.h"
#include "SrcContainer\EngineBaseMapObject.h"

#include "Client_Base_type.h"



#include <ctime>

#include <iostream>
#include <cstdlib>
//using namespace std;




#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <math.h>



namespace cforum
{
	struct elemDate
	{
		size_t day;
		size_t month;
		size_t year;
	};

	class Date
	{
	private:
		elemDate date;
	public:
		Date(size_t y = 1969, size_t m = 1, size_t d = 1)
		{
			date.year = y;
			date.month = m;
			date.day = d;
		}
		Date(std::string str)
		{
			std::vector<std::string> result;
			size_t pos = 0;
			while (1)
			{
				size_t end = str.find('.', pos);
				if (end == str.npos)
				{
					result.push_back(str.substr(pos));
					break;
				}
				else
				{
					result.push_back(str.substr(pos, end - pos));
					pos = end + 1;
				}
			}
			date.year = atoi(result[0].c_str());
			date.month = atoi(result[1].c_str());
			date.day = atoi(result[2].c_str());
		}
		Date(const Date & d)
		{
			date.year = d.getElemDate().year;
			date.month = d.getElemDate().month;
			date.day = d.getElemDate().day;
		}

		elemDate getElemDate()const { return date; }
		size_t getYear()const { return date.year; }
		size_t getMonth()const { return date.month; }
		size_t getDay()const { return date.day; }
		void setYear(size_t y) { date.year = y; }
		void setMonth(size_t m) { date.month = m; }
		void setDay(size_t d) { date.day = d; }

		bool isLeapYear()
		{
			if (date.year % 100 == 0)
			{
				if (date.year % 4 == 0 || date.year % 400 == 0)
					return  true;
				return false;
			}

		}

		bool operator ==(Date & d)const
		{
			return date.year == d.getYear() && date.month == d.getMonth() && date.day == d.getDay();
		}

		bool operator !=(Date & d)const
		{
			return date.year != d.getYear() && date.month != d.getMonth() && date.day != d.getDay();
		}

		Date getDiffDate(Date & d)
		{
			//int year = abs(1);
			//std::abs(date.year - d.getYear()), std::abs(date.month - d.getMonth()), std::abs(date.day - d.getDay())

			return Date(
				abs((long)date.year - (long)d.getYear())
				, abs((long)date.month - (long)d.getMonth())
				, abs((long)date.day - (long)d.getDay())

			);
		}
		Date operator +(const Date & d)
		{
			//сами
			return Date();
		}
		Date  operator -(size_t day)
		{
			//сами
			return Date();
		}
		size_t operator -(Date & d)
		{
			//сами
			return date.day;
		}
	};
}

enum EHOTEL_STATUS
{
	NONE = -1,
	HETY_V_POISKOVOE_VIDACHI = 1,
	SVOBODEN_DL9_ZASELENIA = 2,
	BOOKING_SKAZAL_4TO_MEST_HETY = 3,
	OTSYTSTVUET_V_VIDA4I_AND_BOOKING_SKAZAL_4TO_MEST_HETY = 4,
	SVOBODEN_DL9_ZASELENIA_AND_ZAN9T_V_DRUGOM_DIAPOZONE = 5,
};




class CCalendar
{



public:

	Base::CData  get_data_by_offset(
		int year
		, int month
		, int day
		, int  offset
	)
	{

		struct tm date = { 0, 0, 12 };  // nominal time midday (arbitrary).
		//int year = 2010;
		//int month = 2;  // February
		//int day = 26;   // 26th

		// Set up the date structure
		date.tm_year = year - 1900;
		date.tm_mon = month;  // note: zero indexed
		date.tm_mday = day;       // note: not zero indexed

		// Date, less 100 days
		DatePlusDays(&date, offset);

		std::cout << asctime(&date) << std::endl;
		std::cout << " " << date.tm_year + 1900 << " " << date.tm_mon << " " << date.tm_mday;

		Base::CData Result(date.tm_year + 1900, date.tm_mon, date.tm_mday);

		return Result;
	}

	void CreateCalendar(int DayRequest)
	{
		_Status.reserve(DayRequest);
		_Days.reserve(DayRequest);
		_Cost.reserve(DayRequest);

		for (int i = 1; i < DayRequest; i++)
		{
			Base::CData Day = get_data_by_offset(2020, 2, 25, i);

			_Days.push_back(Day);

			_Status.push_back(EHOTEL_STATUS::HETY_V_POISKOVOE_VIDACHI);
		}
	}


	EHOTEL_STATUS get_status_zalenia(Base::CData Data)
	{
		for (int i = 0; i < _Days.size(); i++)
		{
			if (_Days[i] == Data)
			{
				return  _Status[i];
			}
		}

		return EHOTEL_STATUS::NONE;
	}


	void set_status(Base::CData Data, EHOTEL_STATUS status, float Cost)
	{
		for (int i = 0; i < _Days.size(); i++)
		{
			if (_Days[i] == Data)
			{
				_Status[i] = status;
				_Cost [i] = Cost;
			}
		}

		assert(false);
	}

private:
	// Adjust date by a number of days +/-
	void DatePlusDays(struct tm* date, int days)
	{
		const time_t ONE_DAY = 24 * 60 * 60;

		// Seconds since start of epoch
		time_t date_seconds = mktime(date) + (days * ONE_DAY);

		// Update caller date
		// Use localtime because mktime converts to UTC so may change date
		*date = *localtime(&date_seconds);
	}

	std::vector <EHOTEL_STATUS> _Status;
	std::vector <Base::CData> _Days;
	std::vector <float> _Cost;
};


class CHotelManager
{
public:

	CHotelManager();
	void			Add(client::CHotel Hotel);
	std::string		CreateCalendarNoPeopleInHotel() const;
	std::string		DynamikCost() const;
	bool			FindData(Base::CData DayStart, Base::CData DayEnd);
	int				Size();

	void push_back(CHomeNameAndCostAndData Hotel)
	{
		_ArrHomeNameAndCostAndData.push_back(Hotel);
	}

	void Compute()
	{
		for (CHomeNameAndCostAndData Apart_It : _ArrHomeNameAndCostAndData)
		{
			Base::CData cur_day = Apart_It.get_Level2_data();
			float Cost = Apart_It.GetHome().GetCost();
			EHOTEL_STATUS STARI_STATUS = _CalendarManager.get_status_zalenia(cur_day);
			EHOTEL_STATUS NEW_STATUS;

			if (Apart_It.GetHome().GetCost() > 0)
			{
				NEW_STATUS = EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA;
			}
			else if (Apart_It.GetHome().GetCost() == -1)
			{
				NEW_STATUS = EHOTEL_STATUS::BOOKING_SKAZAL_4TO_MEST_HETY;
			}

			if (STARI_STATUS == EHOTEL_STATUS::BOOKING_SKAZAL_4TO_MEST_HETY)
			{
				if (NEW_STATUS == EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA)
				{
					NEW_STATUS = EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA_AND_ZAN9T_V_DRUGOM_DIAPOZONE;
				}
			}

			if (STARI_STATUS == EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA)
			{
				if (NEW_STATUS == EHOTEL_STATUS::BOOKING_SKAZAL_4TO_MEST_HETY)
				{
					NEW_STATUS = EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA_AND_ZAN9T_V_DRUGOM_DIAPOZONE;
				}
			}

			if (STARI_STATUS == EHOTEL_STATUS::HETY_V_POISKOVOE_VIDACHI)
			{
				if (NEW_STATUS == EHOTEL_STATUS::BOOKING_SKAZAL_4TO_MEST_HETY)
				{
					NEW_STATUS = EHOTEL_STATUS::OTSYTSTVUET_V_VIDA4I_AND_BOOKING_SKAZAL_4TO_MEST_HETY;
				}
			}

			_CalendarManager.set_status(cur_day.startYear, cur_day.startMonth, cur_day.startDay, NEW_STATUS, Cost);

			//_CalendarManager.set_status()
				//_CalendarManager.k
		}
	}




private:
	std::vector<client::CHotel> _Arr;

	std::vector<CHomeNameAndCostAndData> _ArrHomeNameAndCostAndData;

	CCalendar  _CalendarManager;

};


namespace Level1
{
	class CMapDataBase : public CObjectStringContainerMap <CHotelManager>
	{
	public:
		CMapDataBase() {}

		void RenderStat();

		void AddKey(std::vector<std::string> NameHomes);

		void AddValue(client::CHotel Hotel);

		void AddValue(CHomeNameAndCostAndData Hotel)
		{
			/*	Это второй этап. предполагается что все возможные имена отелей уже добавлены.
				теперь будет создана структура, из < лень расписывать..>	*/
			std::string sKey = Hotel.GetHome().create_qniq_key();

			bool bFind = FindObjectByKey(sKey);

			if (bFind)
			{
				auto & it = GetIteratorObject(sKey);
				it->second.push_back(Hotel);
			}
			else
			{
				Log::CFileLog::Log("STRASHNAIA OSHIBKBKA. IM9 OTEL9: " + sKey + "HE HAIDENO V BD", LOG_CALENDAR);
				assert(false);
			}

		}



	};

}


#endif /*CALENDAR_MAP_ADAPTER*/