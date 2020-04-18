#ifndef LOGIC_IMPL_H
#define LOGIC_IMPL_H

#include "def.h"
#include "common.h"
#include "DownloadModul.h"


namespace client
{

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

        static bool IsCurrentDirCreated(CDownLoadList & DownLoadList, CSeting & Seting);

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
