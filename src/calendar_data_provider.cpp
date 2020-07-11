
#include "calendar_data_provider.h"

namespace Level2
{
	void CIteratirDir::Init()
	{
		client::CSeting Seting;

		//for (auto & p : std::experimental::filesystem::directory_iterator(Seting.GetWorkDir()))//old
		for (auto & p : std::experimental::filesystem::directory_iterator(_sRootDir))
		{
			/*
			01.03.2020				// <- Want
			02.03.2020				// <- Want
			03.03.2020				// <- Want
			29.02.2020				// <- Want
				 or
			01.01.2021 - 08.01.2021
			01.02.2021 - 08.02.2021
			01.03.2021 - 08.03.2021
			01.04.2020 - 08.04.2020
			01.05.2020 - 08.05.2020*/

			_DayArr.push_back(p);
		}
	}

	bool CIteratirDir::Get_Next_Intresting_Iterator_Dir(std::string & Result)
	{
		client::CSeting Seting;

		return  Parse_DayMotherYear_DayMotherYear(_DayArr[_Index++], Result);
	}

	std::vector<std::string> CIteratirDir::get_all_file_in_dir(const std::string & sDir, const std::string & sMask)
	{
		std::vector<std::experimental::filesystem::path> Arr = CFileSystem::directory_iterator(sDir);
		std::vector<std::string> HTMLArr = CFileSystem::Filter(Arr, sMask);
		return HTMLArr;
	}

	bool CIteratirDir::Parse_DayMotherYear_DayMotherYear(std::experimental::filesystem::path Path, std::string & Result)
	{

		std::vector<std::experimental::filesystem::path> RequestInterval;

		std::vector<MyData> RasparseArr;

		for (auto p : std::experimental::filesystem::directory_iterator(Path))
		{
			RequestInterval.push_back(p);

			/*  02.03.2020-03.03.2020 // <- Want
				02.03.2020-04.03.2020 // <- Want
				02.03.2020-05.03.2020 // <- Want */
		}



		for (auto it : RequestInterval)
		{
			MyData rasparse = CDataUtil::Parse_DayMotherYear_DayMotherYear(Path.string(), it.string());

			if (rasparse.empty())
			{
				return false;
			}

			int DayStart = rasparse[0];
			int DayEnd = rasparse[3];


			if (abs(DayEnd - DayStart) == 1)
			{
				Log::CFileLog::Log(" return" + it.string(), LOG_CALENDAR);

				Result = it.string();

				return true;
			}

		}

		return false;
	}


	std::string CMyString::do_replace(const std::string & in, const std::string &from, const std::string & to)
	{
		return std::regex_replace(in, std::regex(from), to);
	}

	std::vector <int> CDataUtil::Parse_DayMotherYear_DayMotherYear(const std::string & sPredDir, const std::string & sData)
	{
		Log::CFileLog::Log("[CDataUtil::Parse_DayMotherYear_DayMotherYear] : sPredDir= " + sPredDir + " sData=" + sData, LOG_CALENDAR);

		/*
		input:  sData = D:\Development\booking\bin2\Debug\db\01.03.2020\02.03.2020-03.03.2020
		input: sPredDir D:\Development\booking\bin2\Debug\db\01.03.2020\
		target get int arr {2 3 2020 3 3 2020}
		*/

		if (sData.size() < sPredDir.size())
			return {};

		std::string buf0 = std::string(sData, sPredDir.size() + 1);


		if (buf0.size() != 21)
		{
			return  {};
		}

		//want 02.03.2020-04.03.2020
		std::string buf1 = buf0;// ("02.03.2020-04.03.2020");

		std::string buf;

		buf = CMyString::do_replace(buf1, "\\.", " ");
		buf = CMyString::do_replace(buf, "-", " ");

		std::list<std::string> words;
		std::istringstream ist(buf);
		std::string tmp;

		while (ist >> tmp)
		{
			words.push_back(tmp);
		}


		std::vector <int> numArr;
		for (auto it : words)
			numArr.push_back(std::stoi(it));

		return  numArr;
	}



	std::vector<std::string> CDataProvider::get_all_uniq_key_fom_file(std::string sRootDir)
	{
		std::vector<std::string> ArrName = client::CFileManager::get_all_uniq_key_fom_file(sRootDir);

		if (ArrName.size() != 1)
		{
			Log::CFileLog::Log(
				"[GetAllNameHotelInCurDir::CDataProvider] : Error, HeMojet bit > 1 files: " + std::to_string(ArrName.size())
				+ " " + sRootDir
				, LOG_CALENDAR_ERR);
			return {};
		}

		client::CAllNameFile File_(ArrName[0]);

		//return  { "ALPINA", "GUDAURI404" };
		return File_.GetArrName();
	}

	std::vector<std::string> CDataProvider::GetAllNameHotelInCurDir(std::string sRootDir)
	{
		std::vector<std::string> ArrName = client::CFileManager::GetAllHotelName(sRootDir);

		if (ArrName.size() != 1)
		{
			Log::CFileLog::Log("[GetAllNameHotelInCurDir::CDataProvider] : Error, HeMojet bit > 1 files: " + std::to_string(ArrName.size()), LOG_CALENDAR_ERR);
			return {};
		}

		client::CAllNameFile File_(ArrName[0]);

		//return  { "ALPINA", "GUDAURI404" };
		return File_.GetArrName();
	}


	void CDataProvider::get_assoc_data_by_quniq_key(
		std::vector<CHomeNameAndCostAndData> & Result 
		,const std::string & sRootDir
		, const std::string & sHotelName
	)
	{
		 
		std::vector<CHomeNameAndCostAndData> Objects = CDataProvider::get_array_HomeNameAndCostAndData_by_file(sRootDir);

		for (int i = 0; i < Objects.size(); i++)
		{
			if (Objects[i].GetHome().create_qniq_key() == sHotelName)
			{
				Result.emplace_back(Objects[i]);
			}
		}
	}

	void CDataProvider::FindAsocDataByHomeName(const std::string & sRootDir, const std::string & sHotelName)
	{
		std::vector<CHomeNameAndCostAndData> Objects = CDataProvider::get_array_HomeNameAndCostAndData_by_file(sRootDir);

		for (int i = 0; i < Objects.size(); i++)
		{

			if (Objects[i].GetHome().create_qniq_key() == sHotelName)
			{
				std::string sFileSave = dir_path::CParse::get_path_to_contry(sRootDir) + OS::CSystyem::GetSlash() + FILE_NAME_SPY + "_" + Objects[i].GetHome().GetName() + FILE_FORMAT;

				Log::CFileLog::raw_log("[FindAsocDataByHomeName] "
					+ Objects[i].GetHome().GetName()
					+ " key " + sHotelName
					+ " " + sRootDir
					+ " cost "
					+ std::to_string(Objects[i].GetHome().GetCost())
					, sFileSave);

			}
		}
	}

	/* 
	GetArrHomeNameAndCostAndData
	get_array_HomeNameAndCostAndData_by_file
	*/ 
	std::vector<CHomeNameAndCostAndData> CDataProvider::get_array_HomeNameAndCostAndData_by_file(std::string sIntrestingDir)
	{
		std::vector<std::string> ArrName = client::CFileManager::get_files_name_and_cost(sIntrestingDir);
		//ArrHomeName ArrName = client::CFileManager::GetArrHomeNameAndCost("D:\\Development\\booking\\bin2\\Debug\\db\\29.02.2020\\01.03.2020-04.03.2020");


		Base::CData Start, End, DataLevel2;
		bool bRes = Str::Util::Parse_GetDataByPath(sIntrestingDir, Start, End);
		if (bRes == false)
		{
			Log::CFileLog::Log("[::GetArrHomeNameAndCostAndData] : Parse_GetDataByPath Error. Not parse data by str = " + sIntrestingDir, LOG_CALENDAR_ERR);
		}
		
		bRes = Str::Util::get_level2_data_obj (sIntrestingDir, DataLevel2);
		if (bRes == false)
		{
			Log::CFileLog::Log("[::GetArrHomeNameAndCostAndData] : get_level2_data_obj Error. Not parse data by str = " + sIntrestingDir, LOG_CALENDAR_ERR);
		}


		std::vector <CHomeNameAndCostAndData> Arr;

		for (auto it : ArrName)
		{
			CFileData FileData(it);
			for (CStr Line : FileData.GetArrLine())
			{
				CHome Home = CHome::Deserealize(Line);
				CHomeNameAndCostAndData HomeNameAndCostAndData(Home, Start, End, DataLevel2);
				Arr.push_back(HomeNameAndCostAndData);
			}
		}

		return Arr;
	}

}
