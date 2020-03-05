
#include "calendar_data_provider.h"

namespace Level2
{
	std::string CMyString::do_replace(const std::string & in, const std::string &from, const std::string & to)
	{
		return std::regex_replace(in, std::regex(from), to);
	}
	 
	std::vector <int> CDataUtil::Parse_DayMotherYear_DayMotherYear(const std::string & sPredDir, const std::string & sData)
	{
		Log::CFileLog::Log(sPredDir + "   " + sData, LOG_CALENDAR);

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
	 
	void CIteratirDir::Init()
	{
		client::CSeting Seting;

		for (auto & p : std::experimental::filesystem::directory_iterator(Seting.GetWorkDir()))
		{
			//   01.03.2020				// <- Want
			//   02.03.2020				// <- Want
			//   03.03.2020				// <- Want
			//   29.02.2020				// <- Want
			_DayArr.push_back(p);
		}
	}
		  
	bool CIteratirDir::Get_Next_Intresting_Iterator_Dir(std::string & Result)
	{
		client::CSeting Seting;

		return  Parse_DayMotherYear_DayMotherYear(_DayArr[_Index++], Result);
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
	 
	ArrHomeName CDataProvider::GetAllNameHotelInCurDir(std::string sRootDir)
	{
		ArrHomeName ArrName = client::CFileManager::GetAllHotelName(sRootDir);

		if (ArrName.size() != 1)
		{
			Log::CFileLog::Log("[GetAllNameHotelInCurDir::CDataProvider] : Error, HeMojet bit > 1 files: " + std::to_string(ArrName.size()), LOG_CALENDAR_ERR);
			return {};
		}

		client::CAllNameFile File_(ArrName[0]);

		//return  { "ALPINA", "GUDAURI404" };
		return File_.GetArrName();
	}
	 
	ArrHomeNameAndCostAndData_ CDataProvider::GetArrHomeNameAndCostAndData(std::string sIntrestingDir)
	{
		ArrHomeName ArrName = client::CFileManager::GetArrHomeNameAndCost(sIntrestingDir);
		//ArrHomeName ArrName = client::CFileManager::GetArrHomeNameAndCost("D:\\Development\\booking\\bin2\\Debug\\db\\29.02.2020\\01.03.2020-04.03.2020");


		Base::CData Start, End;
		bool bRes = Str::Util::Parse_GetDataByPath(sIntrestingDir, Start, End);

		if (bRes == false)
		{
			Log::CFileLog::Log("[::GetArrHomeNameAndCostAndData] : Error. Not parse data by str = " + sIntrestingDir, LOG_CALENDAR_ERR);
		}

		std::vector <CHomeNameAndCostAndData> Arr;

		for (auto it : ArrName)
		{
			CFileData FileData(it);
			for (CStr Line : FileData.GetArrLine())
			{
				CHome Home = CHome::Deserealize(Line);
				CHomeNameAndCostAndData HomeNameAndCostAndData(Home, Start, End);
				Arr.push_back(HomeNameAndCostAndData);
			}
		}

		return Arr;
	}

}
