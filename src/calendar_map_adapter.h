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

	static void Deserialize(std::vector<std::string> & Tokens)
	{
		std::string    sKey = Tokens[0];
		std::string     sCountry = Tokens[1];
		std::string     sName = Tokens[2];
		std::string     sDate = Tokens[3];
		std::string     sCostType = Tokens[4];
		std::string     sCost = Tokens[5];
		std::string     sStatus = Tokens[6];

		CHome d(sName,sKey, std::atoi(sCost.c_str()));
		Base::CData day;
		Base::CData::Parse(sDate, day);
		int ssdf = 234;
	}


	static std::string GetStatus(std::vector<std::string> & Tokens)
	{	 
		// Input Atrium432_https://q-cf.bstatic.com/xdata/images/hotel/square200/244215887.jpg?k=833576b71e08c85f5cfe8c4c9333374825f5f86484228e755fac3d5ad9bd2a73&o= Country Atrium432 10.3.2020 BYN 13688 3
		// Output: status  
		std::string sStatus = Tokens[6];
		return sStatus;
	}
	 

	void save_result_compute(CHomeNameAndCostAndData  assoc_apart, const std::string & sFilePath)
	{
		for (int i = 0; i < _Days.size(); i++)
		{
			std::string sStatus;

			if (_Status[i] == EHOTEL_STATUS::BOOKING_SKAZAL_4TO_MEST_HETY)
				sStatus = std::to_string(EHOTEL_STATUS::BOOKING_SKAZAL_4TO_MEST_HETY);

			else if (_Status[i] == EHOTEL_STATUS::HETY_V_POISKOVOE_VIDACHI)
				sStatus = std::to_string(EHOTEL_STATUS::HETY_V_POISKOVOE_VIDACHI);

			else if (_Status[i] == EHOTEL_STATUS::NONE)
				sStatus = std::to_string(EHOTEL_STATUS::NONE);

			else if (_Status[i] == EHOTEL_STATUS::OTSYTSTVUET_V_VIDA4I_AND_BOOKING_SKAZAL_4TO_MEST_HETY)
				sStatus = std::to_string(EHOTEL_STATUS::OTSYTSTVUET_V_VIDA4I_AND_BOOKING_SKAZAL_4TO_MEST_HETY);

			else if (_Status[i] == EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA)
				sStatus = std::to_string(EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA);

			else if (_Status[i] == EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA_AND_ZAN9T_V_DRUGOM_DIAPOZONE)
				sStatus = std::to_string(EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA_AND_ZAN9T_V_DRUGOM_DIAPOZONE);



			std::string sKey = assoc_apart.GetHome().create_qniq_key();
			std::string sCountry = "Country";
			std::string sName = assoc_apart.GetHome().GetName();
			std::string sDate = _Days[i].Serialize();
			std::string sCostType = "BYN";
			std::string sCost = "13688";

			std::string sResult = sKey
				+ " " + sCountry
				+ " " + sName
				+ " " + sDate
				+ " " + sCostType
				+ " " + sCost
				+ " " + sStatus;

			Log::CFileLog::raw_log(sResult, sFilePath);
			Log::CFileLog::raw_log(sResult, sFilePath + FILE_PROCESSING_INFO_RESULT + "_" + sName + FILE_FORMAT);

		}
	}

	Base::CData  get_data_by_offset(
		int year
		, int month
		, int day
		, int  offset
	);

	void CreateCalendar(int DayRequest);


	EHOTEL_STATUS get_status_zalenia(Base::CData Data);


	void set_status(Base::CData Data, EHOTEL_STATUS status, float Cost);

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

		void AddValue(CHomeNameAndCostAndData Hotel);
	};

}


#endif /*CALENDAR_MAP_ADAPTER*/

