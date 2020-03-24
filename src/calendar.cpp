
#include "calendar.h"




namespace client {



	void IDataBase::Init(std::vector<std::experimental::filesystem::path> level3dir)
	{
		int r = 0;
		for (auto it : level3dir)
		{
			std::vector<std::string> Homes = Level2::CDataProvider::get_all_uniq_key_fom_file (it.string());
			_MapDataBase.AddKey(Homes);

			Log::CFileLog::Log(
				" HomesID: " + std::to_string(r++) + "/" + std::to_string(level3dir.size() ) + " "
				, LOG_MAIN_PROD_PARSER);

		}

		std::vector<std::string> Homes = get_all_name_by_init_map();
		 
		int NumHomes = 0, dir_num = 0;
		for (auto dir_it : level3dir)
		{

			for (auto sName : Homes)
			{
				Log::CFileLog::Log(
					" HomesID: " + std::to_string(++NumHomes) + "/" + std::to_string(Homes.size()) + " "
					" Dir: " + std::to_string(dir_num) + "/" + std::to_string(level3dir.size()) +
					" sName " + sName
					, LOG_MAIN_PROD_PARSER);

				Level2::CDataProvider::FindAsocDataByHomeName(dir_it.string(), sName);
			}
			NumHomes = 0;
			++dir_num;


		}
		int g345 = 345;
	}



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
				std::vector<std::string> Homes = Level2::CDataProvider::GetAllNameHotelInCurDir(dat);
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
				std::vector<CHomeNameAndCostAndData> Arr = Level2::CDataProvider::GetArrHomeNameAndCostAndData(dat);

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



