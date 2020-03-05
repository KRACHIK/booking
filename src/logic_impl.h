#ifndef LOGIC_IMPL_H
#define LOGIC_IMPL_H

#include "def.h"
#include "common.h"
#include "DownloadModul.h"

namespace Java {

#define PROPERTIES "props.properties"

	class CProperties
	{
	public:
		CProperties();

		CProperties(
			int startDay
			, int  startMonth
			, int  startYear
			, int  endDay
			, int  endMonth
			, int  endYear
			, const std::string & outputDirectory
		);
	public:

		void CreateProperties(std::string sFileName); 

	private:
		int _startDay;
		int _startMonth;
		int _startYear;
		int _endDay;
		int _endMonth;
		int _endYear;
		std::string _outputDirectory;

	};

}

namespace client
{
	class CTask
	{
	public:

		CTask();
		CTask(Java::CProperties Properties, const std::string & sFullPath, const std::string  & sDirProp);
		std::string GetFullPath();
		std::string GetDirProp();

	private:
		Java::CProperties	_Properties;
		std::string			_sFullPath;
		std::string			_sDirProp;

	};

	class CDwn
	{
	public:
		CDwn();
		CDwn(const std::string & WantFile, CTask  Task);

	public:
		std::string _WantFile;
		CTask _Task;
	};


	class CLogic
	{
	public:
		static bool IsWork();
		static bool  Work();
	private:
		static bool RunUtilParse(const std::vector<CTask> & TaskArr, CSeting Seting);
		static std::vector<CTask> CreateTask(CSeting Seting);
		static bool CreateWorkDir(const std::string & sDirPath);
		static bool UpdateFileProperties(std::string WantFile, std::string  GetFullPath, std::string  GetProgaDir);
		static bool Download(std::string WantFile, CTask it, CDwn & ErrDwnArr);
		static bool Thread_download(std::string WantFile, CTask it);
		static bool CreateSettingForParser(const std::vector<CTask> & TaskArr, CSeting Seting);
		static bool RunUtilDownload(const std::vector<CTask> & TaskArr, CSeting Seting);
		static std::string GetActualWorkDir(const std::string & sDirPath);
	};
}


#endif 