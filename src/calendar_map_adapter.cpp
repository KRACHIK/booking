#include "calendar_map_adapter.h"

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
			��� ������ ����. �������������� ��� ��� ��������� ����� ������ ��� ���������.
			������ ����� ������� ���������, �� ���_�����, �����{����, ���������, �����, ���_�����}
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

}