#ifndef LOGIC_IMPL_H
#define LOGIC_IMPL_H

#include "def.h"
#include "common.h"
#include "DownloadModul.h"


namespace client
{
#if 0
	class CTask
	{
	public:

		CTask();

		CTask(Java::CProperties Properties, const std::string & sFullPath, const std::string  & sDirProp);
		CTask(const std::string & sFullPath, const std::string  & sDirProp);

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
#endif 

	class CLogic
	{
	public:
		static bool IsWork(std::vector<client::CTask> & TaskArr);
		static bool  Work();
		static bool  IsPropuskDwnFile(std::vector<client::CTask> & TaskArr);
		static bool DwnPropuskFile(std::vector<client::CTask> & TaskArr);

	private:
		static bool VozobnovitPrervonuizagruzku(CSeting Seting);
		static bool RunUtilParse(const std::vector<CTask> & TaskArr, CSeting Seting);
		static std::vector<CTask> CreateTask(CSeting Seting);
		static std::vector<CTask> CreateTask_v2_temp(CSeting Seting);
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