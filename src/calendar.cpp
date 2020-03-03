
#include "calendar.h"
 



namespace client {
	 
		void IDataBase::Init()
		{

			{ // Add All Name By All file
				client::CSeting Seting;
				Level2::CIteratirDir  IteratirDir(Seting.GetWorkDir());
				IteratirDir.Init();

				std::string dat;
				while (IteratirDir.Get_Next_Intresting_Iterator_Dir(dat))
				{
					std::cout << "ok" << dat;
					ArrHomeName Homes = Level2::CDataProvider::GetAllNameHotelInCurDir(dat);
					_MapDataBase.AddKey(Homes);
				}
			}

			if (1)
			{
				// Get All HomeNameAndCost by all file in cur dir
				client::CSeting Seting;
				Level2::CIteratirDir  IteratirDir(Seting.GetWorkDir());
				IteratirDir.Init();

				std::string dat;
				while (IteratirDir.Get_Next_Intresting_Iterator_Dir(dat))
				{
					ArrHomeNameAndCostAndData_ Arr = Level2::CDataProvider::GetArrHomeNameAndCostAndData(dat);

					for (CHomeNameAndCostAndData it : Arr)
					{
						client::CHotel Alpina(it.GetHome().GetName(), it.GetHome().GetCost(), it.GetDataStart(), it.GetDataEnd());

						_MapDataBase.AddValue(Alpina);
					}
				}

				Log::CFileLog::Log("Yeah?!", LOG_CALENDAR);

			}
		}

		void IDataBase::RenderStat()
		{
			Log::CFileLog::Log("RenderStat", LOG_CALENDAR);
			_MapDataBase.RenderStat();
		}
		 
}



 