
#include "DownloadModul.h"

namespace Java {

	CProperties::CProperties() {}

	CProperties::CProperties(
		int startDay
		, int  startMonth
		, int  startYear
		, int  endDay
		, int  endMonth
		, int  endYear
		, const std::string & outputDirectory
	) : _startDay(startDay)
		, _startMonth(startMonth)
		, _startYear(startYear)
		, _endDay(endDay)
		, _endMonth(endMonth)
		, _endYear(endYear)
		, _outputDirectory(outputDirectory)
	{
	}
 
	void CProperties::CreateProperties(std::string sFileName)
	{
		std::stringstream ss;

		ss << "startDay=" << _startDay << "\n";
		ss << "startMonth=" << _startMonth << "\n";
		ss << "startYear=" << _startYear << "\n";
		ss << "endDay=" << _endDay << "\n";
		ss << "endMonth=" << _endMonth << "\n";
		ss << "endYear=" << _endYear << "\n";
		ss << "outputDirectory=" << _outputDirectory << "\n";

		std::ofstream outFile(sFileName);
		outFile << ss.rdbuf();
		outFile.close();
	}
}
 
namespace client
{
	CTask::CTask()
	{
	}

	CTask::CTask(
		const std::string & sFullPath,
		const std::string  & sDirProp
	)
		: _sFullPath(sFullPath)
		, _sDirProp(sDirProp)
	{
		int sdf3;
	}

	CTask::CTask(Java::CProperties Properties
		, const std::string & sFullPath,
		const std::string  & sDirProp
	)
		: _Properties(Properties)
		, _sFullPath(sFullPath)
		, _sDirProp(sDirProp)
	{

	}

	std::string CTask::GetFullPath()
	{
		return _sFullPath;
	}


	std::string CTask::GetDirProp()
	{
		return _sDirProp;
	}

	 
	CDwn::CDwn() {}

	CDwn::CDwn(const std::string & WantFile, CTask  Task)
	{
		_WantFile = WantFile;
		_Task = Task;
	}

}

 
bool CDownload::VozobnovitPrervonuizagruzku(client::CSeting Seting)
{
	// получить линк на корень в день в который прервалась загрузка
	// перебрать каждую директорию и убедится в том что файлы скаченны без пропусков
	// если файл не скачен или есть пропуск то
	// получить его property;
	// запустить попытку загрузки

	return false;
}

bool CDownload::IsPropuskDwnFile(const std::string & sDir, std::vector<client::CTask> & TaskArr)
{
	/* input D:\Development\booking\prod2

	get All File
				booking0.html  booking1.html booking10.html booking11.html booking12.html booking13.html
				booking14.html booking15.html booking16.html booking17.html booking18.html ..
		see number 1,2,3,4,5,6
	*/

	std::vector<std::experimental::filesystem::path> Arr = CFileSystem::directory_iterator(sDir);
	std::vector<std::string> HTMLArr = CFileSystem::Filter(Arr, ".html");

	
	if (HTMLArr.empty())
	{

		std::vector<std::string> JavaDwnPropFile = CFileSystem::Filter(Arr, ".properties");

		if (JavaDwnPropFile.size() == 1)
		{ 
			Log::CFileLog::Log("[CDownload::IsPropuskDwnFile] : PropDir" + Arr[0].parent_path().string(), LOG_LOGIC);
			Log::CFileLog::Log("[CDownload::IsPropuskDwnFile] : JavaDwnPropFile: " + JavaDwnPropFile[0],  LOG_LOGIC);

			TaskArr.push_back(client::CTask(JavaDwnPropFile[0], Arr[0].parent_path().string()));
		}
			  
		return true; // подтверждаю пропуск файлов
	}

	std::vector<int> ArrNum;
	for (auto it : HTMLArr)
	{
		// it=       D:\Development\booking\prod2\booking14.html
		// booking =                              booking14
		std::string booking = CFileSystem::GetStemByPath(it);
		std::string sNum = Str::rENAME::do_replace(booking, "booking", " ");
		int Num = std::stoi(sNum);
		ArrNum.push_back(Num);
	}


	std::sort(ArrNum.begin(), ArrNum.end());
	for (int i = 0; i < ArrNum.size() - 1; i++)
	{
		int Num = ArrNum[i];
		int NumNext = ArrNum[i + 1];
		int diff = NumNext - Num;

		if (diff != 1)
		{
			// propusk files
			return true;
		}
	}

	return false; //ok
}

