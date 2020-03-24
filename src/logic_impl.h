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

		static  std::vector<std::string>
			get_all_level1_dir(CDownLoadList & DownLoadList, CSeting  & Seting);


		static std::vector<std::experimental::filesystem::path> 
			get_all_level2_dir(CDownLoadList & DownLoadList, CSeting  & Seting);

		static std::vector<std::experimental::filesystem::path>
			get_all_level3_dir(CDownLoadList & DownLoadList, std::vector<std::experimental::filesystem::path> level2dir, CSeting  & Seting);
		 

		static bool IsWork(std::vector<client::CTask> & TaskArr);
		static bool Work();
		static bool DwnPropuskFile(std::vector<client::CTask> & TaskArr);

		static bool IsPropuskDwnFile(CDownLoadList & DownLoadList, std::vector<client::CTask> & TaskArr, CSeting & Seting);
		static bool CreateTaskForMoreCountry(CDownLoadList & DownLoadList, std::vector<client::CTask> & TaskArr, CSeting & Seting);

		static bool IsCurrentDirCreated(CDownLoadList & DownLoadList, CSeting & Seting)
		{
			// Xodit po stranam
			for (auto it : DownLoadList.get_valid_link())
			{

				// set current country for setting object
				std::string  sCountryIndex;
				bool bRet = DownLoadList.get_dest_by_link(it, sCountryIndex);
				Seting.set_work_country_dir(sCountryIndex);
				Seting.set_country(sCountryIndex);


				std::string ActualWorkDir = GetActualWorkDir(Seting.GetWorkDir()); //D:\Development\booking\bin2\Debug\db\04.03.2020

				if (std::experimental::filesystem::exists(ActualWorkDir))
				{

					Log::CFileLog::Log("estb" + ActualWorkDir, LOG_LOGIC);
				}
				else
				{
					Log::CFileLog::Log("Nety" + ActualWorkDir, LOG_LOGIC);

					return false;
				}
			}
			return true;
		}

		static bool RunUtilDownload(const std::vector<CTask> & TaskArr, CSeting & Seting);

	private:
		static bool VozobnovitPrervonuizagruzku(CSeting Seting);
		static bool RunUtilParse(const std::vector<CTask> & TaskArr, CSeting & Seting);
		static std::vector<CTask> CreateTask(CSeting Seting);
		static std::vector<CTask> CreateTask_v2_temp(CSeting Seting);
		static bool CreateWorkDir(const std::string & sDirPath);
		static bool UpdateFileProperties(std::string WantFile, std::string  GetFullPath, std::string  GetProgaDir);
		static bool Download(std::string WantFile, CTask it, CDwn & ErrDwnArr);
		static bool Thread_download(std::string WantFile, CTask it);
		static bool CreateSettingForParser(const std::vector<CTask> & TaskArr, CSeting Seting);
		static std::string GetActualWorkDir(const std::string & sDirPath);
	};
}


#endif 