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



class CHotelManager
{
public:
	CHotelManager() { }

	void Add(client::CHotel Hotel);

	std::string CreateCalendarNoPeopleInHotel() const
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

	std::string  DynamikCost() const
	{
		std::string sAllCost;

		for (auto it : _Arr)
			sAllCost += " " + std::to_string(it._Cost);

		return _Arr[0]._sName + " Cost " + sAllCost;
	}

	bool FindData(Base::CData DayStart, Base::CData DayEnd)
	{  
		for (auto it : _Arr)
		{
			if (it._DayStart == DayStart && it._DayEnd == DayEnd )
			{
				return true;
			}
		}
		 
		return false;
	}

	int Size() { return _Arr.size(); }
private:
	std::vector<client::CHotel> _Arr;
};




namespace Level1
{
	class CMapDataBase : public CObjectStringContainerMap <HotelForCalendar>
	{
	public:
		CMapDataBase() { }

		void RenderStat();

		void AddKey(ArrHomeName NameHomes);

		void AddValue(client::CHotel Hotel);

	};

}


#endif /*CALENDAR_MAP_ADAPTER*/