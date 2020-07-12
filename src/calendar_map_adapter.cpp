#include "calendar_map_adapter.h"

#ifdef QT_COMPILER
#include<bits/stdc++.h>
#else
#endif


// Return if year is leap year or not.
bool isLeap(int y)
{
    if (y%100 != 0 && y%4 == 0 || y %400 == 0)
        return true;

    return false;
}

// Given a date, returns number of days elapsed
// from the beginning of the current year (1st
// jan).
int offsetDays(int d, int m, int y)
{
    int offset = d;

    switch (m - 1)
    {
    case 11:
        offset += 30;
    case 10:
        offset += 31;
    case 9:
        offset += 30;
    case 8:
        offset += 31;
    case 7:
        offset += 31;
    case 6:
        offset += 30;
    case 5:
        offset += 31;
    case 4:
        offset += 30;
    case 3:
        offset += 31;
    case 2:
        offset += 28;
    case 1:
        offset += 31;
    }

    if (isLeap(y) && m > 2)
        offset += 1;

    return offset;
}

// Given a year and days elapsed in it, finds
// date by storing results in d and m.
void revoffsetDays(int offset, int y, int *d, int *m)
{
    int month[13] = { 0, 31, 28, 31, 30, 31, 30,
                    31, 31, 30, 31, 30, 31 };

    if (isLeap(y))
        month[2] = 29;

    int i;
    for (i = 1; i <= 12; i++)
    {
        if (offset <= month[i])
            break;
        offset = offset - month[i];
    }

    *d = offset;
    *m = i;
}

// Add x days to the given date.
Base::CData  addDays(int d1, int m1, int y1, int x)
{
    int offset1 = offsetDays(d1, m1, y1);
    int remDays = isLeap(y1)?(366-offset1):(365-offset1);

    // y2 is going to store result year and
    // offset2 is going to store offset days
    // in result year.
    int y2, offset2;
    if (x <= remDays)
    {
        y2 = y1;
        offset2 = offset1 + x;
    }

    else
    {
        // x may store thousands of days.
        // We find correct year and offset
        // in the year.
        x -= remDays;
        y2 = y1 + 1;
        int y2days = isLeap(y2)?366:365;
        while (x >= y2days)
        {
            x -= y2days;
            y2++;
            y2days = isLeap(y2)?366:365;
        }
        offset2 = x;
    }

    // Find values of day and month from
    // offset of result year.
    int m2, d2;
    revoffsetDays(offset2, y2, &d2, &m2);

    std::cout << "d2 = " << d2 << ", m2 = " << m2
        << ", y2 = " << y2 << "\n";
    return Base::CData (d2, m2, y2);
}

void CHotelManager::Add(client::CHotel Hotel)
{
	_Arr.push_back(Hotel);
}

CHotelManager::CHotelManager()
{
}

std::string CHotelManager::CreateCalendarNoPeopleInHotel() const
{
	std::string sAllData;
	std::string sAllCost;

	for (auto it : _Arr)
	{
		sAllData += " [" + it.GetDataString() + "] ";
		sAllCost += " [" + std::to_string(it._Cost) + "] ";
	}

	return _Arr[0]._sName + sAllData + " Cost " + sAllCost;
}

std::string CHotelManager::DynamikCost() const
{
	std::string sAllCost;

	for (auto it : _Arr)
		sAllCost += " " + std::to_string(it._Cost);

	return _Arr[0]._sName + " Cost " + sAllCost;
}

bool CHotelManager::FindData(Base::CData DayStart, Base::CData DayEnd)
{
	for (auto it : _Arr)
	{
		if (it._DayStart == DayStart && it._DayEnd == DayEnd)
		{
			return true;
		}
	}

	return false;
}

int CHotelManager::Size() { return _Arr.size(); }

void CHotelManager::push_back(CHomeNameAndCostAndData Hotel)
{
	_ArrHomeNameAndCostAndData.push_back(Hotel);
}

bool CHotelManager::is_init()
{
	bool pusto = _ArrHomeNameAndCostAndData.empty();
	return !pusto;
}

void CHotelManager::Compute()
{
	_CalendarManager.CreateCalendar(180);

	for (CHomeNameAndCostAndData Apart : _ArrHomeNameAndCostAndData)
	{
		Base::CData cur_day = Apart.get_Level2_data();
		float Cost = Apart.get_cost();
		EHOTEL_STATUS STARI_STATUS = _CalendarManager.get_status_zalenia(cur_day);

		if (STARI_STATUS == EHOTEL_STATUS::NONE)
		{
			Log::CFileLog::Log("[Compute] : STRASHNAI9 ERROR", LOG_CALENDAR_ERR);
			assert(false);
		}


		EHOTEL_STATUS NEW_STATUS;

		if (Apart.get_cost() > 0)
		{
			NEW_STATUS = EHOTEL_STATUS::SVOBODEN_DL9_ZASELENIA;
		}
		else if (Apart.get_cost() == -1)
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

		_CalendarManager.set_status(cur_day, NEW_STATUS, Cost);
	}
}

void CHotelManager::save_result_compute(std::string sFilePath)
{
	if (is_init())
	{
		_CalendarManager.save_result_compute(_ArrHomeNameAndCostAndData[0], sFilePath);
	}
	else
	{
		Log::CFileLog::Log("[save_result_compute] : is_init() = false. Error.", LOG_CALENDAR_ERR);
	}
}



#ifdef QT_COMPILER
    // zero
#else
namespace Level1
{
	void CMapDataBase::RenderStat()
	{
		for (auto it = GetMap().begin(); it != GetMap().end(); it++)
		{
			std::string sReport = it->second.CreateCalendarNoPeopleInHotel();
			Log::CFileLog::Log("[CMapDataBase::RenderStat] :" + sReport, "CreateCalendarNoPeopleInHotel.txt");
		}

		for (auto it = GetMap().begin(); it != GetMap().end(); it++)
		{
			std::string sReport = it->second.DynamikCost();
			Log::CFileLog::Log("[CMapDataBase::RenderStat] :" + sReport, "CreateDynamikCost.txt");
		}
	}


	void CMapDataBase::AddKey(std::vector<std::string> NameHomes)
	{
		//Log::CFileLog::Log("AddKey: Start", LOG_CALENDAR);
		for (auto it : NameHomes)
		{
			//Log::CFileLog::Log("AddKey: " + it, LOG_CALENDAR);
			Insert(it, CHotelManager());
		}
	}


	void CMapDataBase::AddValue(client::CHotel Hotel)
	{
		/*
			Ёто второй этап. предполагаетс€ что все возможные имена отелей уже добавлены.
			теперь будет создана структура, из »ћя_ќ“≈Ћя,  Ћј——{ƒј“ј, ƒј“ј ќЌ÷ј, ÷≈ЌЌј, »ћя_ќ“≈Ћя}
		*/
		std::string sKey = Hotel._sName;

		bool bFind = FindObjectByKey(sKey);

        if (bFind)
		{
			auto & it = GetIteratorObject(sKey);

			if (it->second.Size() > 0)
			{
				int df23 = 32423;
			}


			bool bFind = it->second.FindData(Hotel._DayStart, Hotel._DayEnd);

			if (bFind == false)
			{
				it->second.Add(Hotel);
			}
			else
			{
				int asdf = 345;
			}

		}
		else
		{
			Log::CFileLog::Log("STRASHNAIA OSHIBKBKA. IM9 OTEL9: " + sKey + "HE HAIDENO V BD", LOG_CALENDAR);
			assert(false);
        }
	}

	void CMapDataBase::AddValue(CHomeNameAndCostAndData Hotel)
	{
		/*	Ёто второй этап. предполагаетс€ что все возможные имена отелей уже добавлены.
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

}
#endif

cforum::Date::Date(size_t y, size_t m, size_t d)
{
	date.year = y;
	date.month = m;
	date.day = d;
}

cforum::Date::Date(std::string str)
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

cforum::Date::Date(const Date & d)
{
	date.year = d.getElemDate().year;
	date.month = d.getElemDate().month;
	date.day = d.getElemDate().day;
}

bool cforum::Date::isLeapYear()
{
	if (date.year % 100 == 0)
	{
		if (date.year % 4 == 0 || date.year % 400 == 0)
			return  true;
		return false;
	}

}



Base::CData CCalendar::get_data_by_offset(int year, int month, int day, int offset)
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

	//std::cout << asctime(&date) << std::endl;
	//std::cout << " " << date.tm_year + 1900 << " " << date.tm_mon << " " << date.tm_mday;

	Base::CData Result(
		date.tm_mday
		, date.tm_mon
		, date.tm_year + 1900
	);

	//CData(int startDay_, int startMonth_, int startYear_);

	return Result;
}

void CCalendar::CreateCalendar(int DayRequest)
{
	_Status.reserve(DayRequest);
	_Days.reserve(DayRequest);
	_Cost.reserve(DayRequest);

	for (int i = 1; i < DayRequest; i++)
	{
        /*Base::CData Day = get_data_by_offset(2020, 2, 1, i);
        v funce  get_data_by_offset error ona vernet he vernuiy daty 30.03.2020 doljno bit 31.03.2020
        */
        Base::CData Day2 = addDays(1,2,2020, i);

        _Days.push_back(Day2);

		_Status.push_back(EHOTEL_STATUS::HETY_V_POISKOVOE_VIDACHI);

		_Cost.push_back(0);
	}
}

EHOTEL_STATUS CCalendar::get_status_zalenia(Base::CData Data)
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

void CCalendar::set_status(Base::CData Data, EHOTEL_STATUS status, float Cost)
{
	for (int i = 0; i < _Days.size(); i++)
	{
		if (_Days[i] == Data)
		{
			_Status[i] = status;
			_Cost[i] = Cost;

			return;
		}
	}

	{
        Log::CFileLog::Log("[CCalendar::set_status] : ERROR HASHLA APART, NO NE NASHLA, CLETKY V KALENDARE", LOG_CALENDAR_ERR);
        assert(false);
	}

	//assert(false);
}

// Adjust date by a number of days +/-

void CCalendar::DatePlusDays(tm * date, int days)
{
	const time_t ONE_DAY = 24 * 60 * 60;

	// Seconds since start of epoch
	time_t date_seconds = mktime(date) + (days * ONE_DAY);

	// Update caller date
	// Use localtime because mktime converts to UTC so may change date
	*date = *localtime(&date_seconds);
}
