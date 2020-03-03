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
	CHotelManager()
	{
	}

	void Add(client::CHotel Hotel)
	{
		_Arr.push_back(Hotel);
	}

	void CreateCalendar()
	{
		for (auto it : _Arr)
		{
			Log::CFileLog::Log(it._sName + " " + it.GetDataString() + " " + std::to_string(it._Cost), LOG_CALENDAR);
		}
	}


private:
	std::vector<client::CHotel> _Arr;
};

namespace Level1
{
	class CMapDataBase : public CObjectStringContainerMap <HotelForCalendar>
	{
	public:
		CMapDataBase() { }

		void RenderStat()
		{
			for (auto it = GetMap().begin(); it != GetMap().end(); it++)
			{
				it->second.CreateCalendar();
			}

		}

		void AddKey(ArrHomeName NameHomes)
		{
			Log::CFileLog::Log("AddKey: Start", LOG_CALENDAR);

			for (auto it : NameHomes)
			{
				Log::CFileLog::Log("AddKey: " + it, LOG_CALENDAR);
				Insert(it, HotelForCalendar());
			}
		}

		void DBG_print()
		{

		}

		void AddValue(client::CHotel Hotel)
		{
			/*
				Это второй этап. предполагается что все возможные имена отелей уже добавлены.
				теперь будет создана структура, из ИМЯ_ОТЕЛЯ, КЛАСС{ДАТА, ДАТАКОНЦА, ЦЕННА, ИМЯ_ОТЕЛЯ}
			*/
			std::string sKey = Hotel._sName;

			bool bFind = FindObjectByKey(sKey);

			if (bFind)
			{
				auto & it = GetIteratorObject(sKey);
				it->second.Add(Hotel);
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