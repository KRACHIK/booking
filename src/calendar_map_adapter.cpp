#include "calendar_map_adapter.h"
 
void CHotelManager::Add(client::CHotel Hotel)
{
	_Arr.push_back(Hotel);
}
  
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


	void CMapDataBase::AddKey(ArrHomeName NameHomes)
	{
		Log::CFileLog::Log("AddKey: Start", LOG_CALENDAR);

		for (auto it : NameHomes)
		{
			Log::CFileLog::Log("AddKey: " + it, LOG_CALENDAR);
			Insert(it, HotelForCalendar());
		}
	}


	void CMapDataBase::AddValue(client::CHotel Hotel)
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

}