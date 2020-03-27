
#include "common.h"

namespace Log {

	void CFileLog::Log(const std::string & Str, const std::string & sFileName)
	{
		struct tm *u;
		char s1[40] = { 0 }, s2[40] = { 0 };
		const time_t timer = time(NULL);
		u = localtime(&timer);
		strftime(s1, 80, "[%d.%m.%Y %H:%M:%S] ", u);

		std::stringstream ss;

		ss << s1 << Str << "\n";

		std::ofstream outFile(sFileName, std::ios::app);
		outFile << ss.rdbuf();
		outFile.close();

		std::cout << s1 << Str << "\n";
	}

	void CFileLog::raw_log(const std::string & Str, const std::string & sFileName)
	{
		std::stringstream ss;

		ss << Str << "\n";
		std::ofstream outFile(sFileName, std::ios::app);
		outFile << ss.rdbuf();
		outFile.close();
	}
}

namespace Base
{
#if 1

	CData::CData() {}

	CData::CData(int startDay_, int startMonth_, int startYear_)
		: startDay(startDay_)
		, startMonth(startMonth_)
		, startYear(startYear_)
	{

	}

	bool CData::Parse(const std::string & Src, CData & Start, CData & End)
	{
		dati d = Str::rENAME::Parse_GetDataByPath(Src);

		if (d.size() != 6)
		{
			return false;
		}

		Start = CData(d[0], d[1], d[2]);
		End = CData(d[3], d[4], d[5]);

		return  true;
	}


	bool CData::Parse(const std::string & Src, CData & OutPutData)
	{
		dati d = Str::rENAME::Parse_day_mother_year (Src);

		if (d.size() != 3)
		{
			return false;
		}

		OutPutData = CData(d[0], d[1], d[2]);

		return  true;
	}

#endif 

	std::string CUtil::GetDirByFilePath(const std::string & sGrabDirByFilePath, const CStr & sFileName)
	{
		struct tm *u;
		char s1[40] = { 0 }, s2[40] = { 0 };
		const time_t timer = time(NULL);
		u = localtime(&timer);
		strftime(s1, 80, "%d.%m.%Y_%H-%M-%S", u);

		std::size_t found = sGrabDirByFilePath.find(".html");

		std::string Path;
		if (found != std::string::npos)
		{
			Path = std::string(sGrabDirByFilePath, 0, found) + "_" + sFileName + "_" + s1 + FILE_FORMAT;
		}
		return Path;
	}

	std::string CUtil::GetDirByFilePath(std::string sFileHTML)
	{
		struct tm *u;
		char s1[40] = { 0 }, s2[40] = { 0 };
		const time_t timer = time(NULL);
		u = localtime(&timer);
		strftime(s1, 80, "%d.%m.%Y_%H-%M-%S ", u);

		std::size_t found = sFileHTML.find(".html");
		std::string Path;
		if (found != std::string::npos)
		{
			Path = std::string(sFileHTML, 0, found) + "_" + s1 + ".txt";
		}
		return Path;
	}



}

namespace L2
{


	std::string CData::GetStringCurrentDaraAndOffsetDay(int ADD_DAYS)
	{
		struct tm *u;
		char s1[40] = { 0 }, s2[40] = { 0 };
		const time_t timer = time(NULL);
		u = localtime(&timer);
		strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", u);
		u->tm_mday += ADD_DAYS;
		time_t next = mktime(u);
		u = localtime(&next);
		strftime(s2, 80, "%d.%m.%Y", u);

		return  std::string(s2);
	}

	Base::CData CData::GetStringCurrentDaraAndOffsetDay2(int ADD_DAYS)
	{
		struct tm *u;
		char  day[40] = { 0 }, month[40] = { 0 }, year[40] = { 0 };

		const time_t timer = time(NULL);
		u = localtime(&timer);
		u->tm_mday += ADD_DAYS;
		time_t next = mktime(u);
		u = localtime(&next);

		strftime(day, 80, "%d ", u);
		strftime(month, 80, "%m", u);
		strftime(year, 80, "%Y", u);

		Base::CData da;
		da.startDay = std::stoi(day);
		da.startMonth = std::stoi(month);
		da.startYear = std::stoi(year);

		return da;
	}

	Base::CData CData::GetCurData()
	{
		struct tm *u;
		char  day[40] = { 0 }, month[40] = { 0 }, year[40] = { 0 };
		const time_t timer = time(NULL);
		u = localtime(&timer);


		strftime(day, 80, "%d ", u);
		strftime(month, 80, "%m", u);
		strftime(year, 80, "%Y", u);

		Base::CData da;

		da.startDay = std::stoi(day);
		da.startMonth = std::stoi(month);
		da.startYear = std::stoi(year);

		return da;
	}

}

namespace OS {

	std::string CSystyem::GetSlash()
	{
		//return "\\";
		return "//";
	}

}

namespace client
{
	CAllNameFile::CAllNameFile(const std::string & sFileName)
		: _sFileName(sFileName)
	{
		Open(sFileName);
	}


	void CAllNameFile::Open(const std::string & sFileName)
	{
		CStr line;
		std::ifstream in(sFileName);

		if (in.is_open())
		{
			while (getline(in, line))
			{
				_ArrName.push_back(line);
			}
		}
		else
		{
			Log::CFileLog::Log("Error Open file " + sFileName, LOG_CALENDAR_ERR);
		}
		in.close();
	}


	CSeting::CSeting()
	{
		_sWorkDir = "D://Development//booking//bin2//Debug//db";
		_sProgaDir = "D://Development//booking//bin2//Debug";
	}


	void CSeting::set_work_country_dir(const std::string & sPrefixDir)
	{
		_sWorkCountryDir = _sWorkDir + OS::CSystyem::GetSlash() + sPrefixDir;
	}


	std::string CSeting::GetProgaDir() const
	{
		return _sProgaDir;
	}

	int CSeting::GetDay() const
	{
		return _Day;
	}

	std::string CSeting::GetWorkDir() const
	{
		if (_sWorkCountryDir.empty())
			return _sWorkDir;
		else
			return _sWorkCountryDir;

	}

	std::string CSeting::GetWorkDirAndCurrentDay() const
	{
		std::string sPropDirName = GetWorkDir() + OS::CSystyem::GetSlash() + L2::CData::GetStringCurrentDaraAndOffsetDay(0);
		return sPropDirName;
	}



	CHotel::CHotel(
		std::string  sName
		, int  Cost
		, Base::CData DayStart
		, Base::CData DayEnd
	)
	{
		_sName = sName;
		_Cost = Cost;
		_DayStart = DayStart;
		_DayEnd = DayEnd;
	}

	std::string CHotel::GetDataString()
	{
		return std::string(
			std::to_string(_DayStart.startDay) + "." +
			std::to_string(_DayStart.startMonth) + "." +
			std::to_string(_DayStart.startYear) +
			"-" +
			std::to_string(_DayEnd.startDay) + "." +
			std::to_string(_DayEnd.startMonth) + "." +
			std::to_string(_DayEnd.startYear)
		);

	}


	std::vector<std::string> CFileManager::get_all_uniq_key_fom_file(std::string sPath)
	{
		return CFileSystem::GetFileByMask(sPath, FILE_UNIQ_APART_KEY);
	}

	std::vector<std::string>  CFileManager::GetAllHotelName(std::string sPath)
	{
		//std::vector<std::string>  
		return  CFileSystem::GetFileByMask(sPath, ALL_NAME_HOTEL_BY_ALL_FILE_IN_THIS_DIR);
	}

	std::vector<std::string> CFileManager::GetArrHomeNameAndCost(std::string sPath)
	{
		//std::vector<std::string>  
		return  CFileSystem::GetFileByMask(sPath, NAME_AND_COST);
	}

}


#if 1
namespace Str {

	std::vector <CStr> Util::Parse_Space(const std::string & buf)
	{
		std::vector<std::string>words;

		std::istringstream ist(buf);
		std::string tmp;

		while (ist >> tmp)
			words.push_back(tmp);

		return words;
	}


	std::string Util::do_replace(const std::string & in, const std::string &from, const std::string & to)
	{
		return std::regex_replace(in, std::regex(from), to);
	}

	//std::vector<std::string> ArrName = client::CFileManager::GetArrHomeNameAndCost(sIntrestingDir);
		//ArrHomeName ArrName = client::CFileManager::GetArrHomeNameAndCost("D:\\Development\\booking\\bin2\\Debug\\db\\29.02.2020\\01.03.2020-04.03.2020");

	std::string Util::get_level2_name(const std::string & Path)
	{
		/*-------D:\Development\booking\bin2\Debug\db\-2326178\08.03.2020\09.03.2020-11.03.2020
		----------------------------------------------Levle-1----Levle-2---------Levle-3   */

		//input  D:\\Development\\booking\\bin2\\Debug\\db\\29.02.2020\\01.03.2020-04.03.2020
		//target 29.02.2020
		int AllSize = Path.size();
		int StartSym = AllSize - 32;

		std::string Result = std::string(Path, StartSym, 10);

		return Result;
	}

	bool Util::get_level2_data_obj(const std::string & sData, Base::CData & OutPutPresult)
	{
		//input  D:\\Development\\booking\\bin2\\Debug\\db\\29.02.2020\\01.03.2020-04.03.2020
		//target Base::CData

		std::string StrLevel2 = Util::get_level2_name(sData); //29.02.2020	
		  
		return Base::CData::Parse(StrLevel2, OutPutPresult);
	}


	bool Util::Parse_GetDataByPath(const std::string & buf, Base::CData & Start, Base::CData & End)
	{
		//input  D:\Development\booking\bin2\Debug\db\29.02.2020\01.03.2020-04.03.2020\FILE.TXT
		//target  01.03.2020 04.03.2020

		std::string PathAndSpace = do_replace(buf, "\\\\", " ");
		std::vector <CStr> Arr = Parse_Space(PathAndSpace);

		CStr DiapozonDat = Arr[Arr.size() - 1];

		return Base::CData::Parse(DiapozonDat, Start, End);
	}

}

#endif
