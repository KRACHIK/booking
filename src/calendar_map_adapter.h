#ifndef CALENDAR_MAP_ADAPTER
#define CALENDAR_MAP_ADAPTER

#include "common.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


#ifdef QT_COMPILER
	// zero
#else
	#include "calendar_data_provider.h"
	#include "foreach_dir.h"
    #include "SrcContainer\EngineBaseMapObject.h"
#endif

#include "calendar_def.h"
#include "Client_Base_type.h"
#include "common.h"


#include <ctime>

#include <iostream>
#include <cstdlib>

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
		Date(size_t y = 1969, size_t m = 1, size_t d = 1);
		
		Date(std::string str);
		Date(const Date & d);

		elemDate getElemDate()const { return date; }
		size_t getYear()const { return date.year; }
		size_t getMonth()const { return date.month; }
		size_t getDay()const { return date.day; }
		void setYear(size_t y) { date.year = y; }
		void setMonth(size_t m) { date.month = m; }
		void setDay(size_t d) { date.day = d; }

		bool isLeapYear();

		bool operator ==(Date & d)const
		{
			return date.year == d.getYear() && date.month == d.getMonth() && date.day == d.getDay();
		}

		bool operator !=(Date & d)const
		{
			return date.year != d.getYear() && date.month != d.getMonth() && date.day != d.getDay();
		}
		 
		Date  getDiffDate(Date & d)
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

    static void Deserialize(std::vector<std::string> & Tokens);

    static std::string GetStatus(std::vector<std::string> & Tokens);
	 

    void save_result_compute(CHomeNameAndCostAndData  assoc_apart, const std::string & sFilePath);

    Base::CData  get_data_by_offset( int year , int month , int day , int  offset );

	void CreateCalendar(int DayRequest);

    EHOTEL_STATUS get_status_zalenia(Base::CData Data);

    void set_status(Base::CData Data, EHOTEL_STATUS status, float Cost);

    int get_size(EHOTEL_STATUS Stat);

private:
	// Adjust date by a number of days +/-
	void DatePlusDays(struct tm* date, int days);

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

	void push_back(CHomeNameAndCostAndData Hotel);

	bool is_init();

	void Compute();

	void save_result_compute(std::string sFilePath);

    int get_count_day_svoboden_dl9_zaseleniya();

private:
	std::vector<client::CHotel> _Arr;
	std::vector<CHomeNameAndCostAndData> _ArrHomeNameAndCostAndData;
	CCalendar  _CalendarManager;
};




#ifdef QT_COMPILER
    // zero
#else
namespace Level1
{
	class CMapDataBase : public CObjectStringContainerMap <CHotelManager>
	{
	public:
		CMapDataBase() {}

		void RenderStat();

		void AddKey(std::vector<std::string> NameHomes);

		void AddValue(client::CHotel Hotel);

		void AddValue(CHomeNameAndCostAndData Hotel);
	};
}
#endif


#endif /*CALENDAR_MAP_ADAPTER*/

