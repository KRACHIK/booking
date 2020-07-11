
#include "calendar.h"




namespace client {



	void IDataBase::Serialize(CHomeNameAndCostAndData Hotel)
	{
		std::string Serialize = Hotel.Serialize();

		Log::CFileLog::raw_log(Serialize, "yeah.txt");

		//std::stringstream ss;
		//ss << Serialize << "\n";
		//
		//std::ofstream outFile("yeah.txt");
		//outFile << ss.rdbuf();
		//outFile.close();
	}

	void IDataBase::create_db_for_vital()
	{
		std::vector<std::string> Homes = get_all_name_by_init_map();

		int i = 0, size = _MapDataBase.GetMap().size();

		for (auto it = _MapDataBase.GetMap().begin(); it != _MapDataBase.GetMap().end(); ++it)
		{

			if (it->second.is_init())
			{
				Log::CFileLog::Log("Calendar Task: " + std::to_string(++i) + "/" + std::to_string(size), LOG_MAIN_DATA_OB_ODNOM_OTELE);
				it->second.Compute();
				it->second.save_result_compute("assoc_data.txt");
			}
			else
				Log::CFileLog::Log("Calendar error: " + std::to_string(++i) + "/" + std::to_string(size), LOG_MAIN_DATA_OB_ODNOM_OTELE);

		}
	}


	void IDataBase::Deserealize(std::string sFilePatth)
	{

		client::CAllNameFile File_(sFilePatth);

		int count_line_in_one_raw_object = 2;

		std::vector<std::string> pFileDataLine = File_.GetArrName();

		int CountObject = pFileDataLine.size() / CHomeNameAndCostAndData::count_line_in_one_raw_object();

		int Index = 0;
		for (int i = 0; i < CountObject; i++)
		{
			const std::string & sLine_1 = pFileDataLine[Index];
			Index++;

			const std::string & sLine_2 = pFileDataLine[Index];
			Index++;

			CHomeNameAndCostAndData Object = CHomeNameAndCostAndData::Derialize(sLine_1, sLine_2);
			Log::CFileLog::Log(" object: " + std::to_string(i) + "/" + std::to_string(CountObject), LOG_CALENDAR);

			_MapDataBase.AddValue(Object);

			/*if (Index == 4000)
				break;*/
		}
	}

	void IDataBase::Write_All_Hotel_to_db(std::vector<std::experimental::filesystem::path> level3dir)
	{
		std::vector<std::string> Homes = get_all_name_by_init_map();

		int NumHomes = 0, dir_num = 0;

		// hoodit po katalogam 
		for (auto dir_it : level3dir)
		{

			// get all full info ob hotele
			std::vector<CHomeNameAndCostAndData> Arr = Level2::CDataProvider::get_array_HomeNameAndCostAndData_by_file(dir_it.string());

			for (auto itHotel : Arr)
			{
				Serialize(itHotel);
			}

			/*for (auto sName : Homes) {
			}*/
			Log::CFileLog::Log(" HomesID: " + std::to_string(++NumHomes) + "/" + std::to_string(Homes.size()) + " Dir: " + std::to_string(dir_num) + "/" + std::to_string(level3dir.size()), LOG_MAIN_PROD_PARSER);

			++dir_num;
		}

		int g345 = 345;
	}


	void IDataBase::Init_all_name(std::vector<std::experimental::filesystem::path> level3dir)
	{
		int r = 0;
		for (auto it : level3dir)
		{
			std::vector<std::string> Homes = Level2::CDataProvider::get_all_uniq_key_fom_file(it.string());
			_MapDataBase.AddKey(Homes);

			Log::CFileLog::Log(" HomesID: " + std::to_string(r++) + "/" + std::to_string(level3dir.size()) + " ", LOG_MAIN_PROD_PARSER);

		}
	}

	void IDataBase::Init_and_dolgi_obschet_raboti_kajdogo_otel9(std::vector<std::experimental::filesystem::path> level3dir)
	{
		int r = 0;
		for (auto it : level3dir)
		{
			std::vector<std::string> Homes = Level2::CDataProvider::get_all_uniq_key_fom_file(it.string());
			_MapDataBase.AddKey(Homes);

			Log::CFileLog::Log(
				" HomesID: " + std::to_string(r++) + "/" + std::to_string(level3dir.size()) + " "
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
				std::vector<CHomeNameAndCostAndData> Arr = Level2::CDataProvider::get_array_HomeNameAndCostAndData_by_file(dat);

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

	std::vector<std::string> IDataBase::get_all_name_by_init_map()
	{
		std::vector<std::string> Names;
		for (auto it = _MapDataBase.GetMap().begin(); it != _MapDataBase.GetMap().end(); ++it)
		{
			Names.push_back(
				it->first
			);
		}
		return Names;
		//std::vector<std::string>
	}

}



