#ifndef LOGIC_IMPL_H
#define LOGIC_IMPL_H

#include "def.h"
#include "common.h"
#include "DownloadModul.h"
#include "foreach_dir.h"


namespace client
{

	class CLogic
	{
	public:

		/* CLogic::get_path_for_run_utils
		output: 
				{  "D:\Development\booking\bin2\Debug\db\-2326178\03.09.2020\04.09.2020-11.09.2020"
				  ,"D:\Development\booking\bin2\Debug\db\-2326178\03.09.2020\04.09.2020-11.09.2020"
				  ,"..."
		        }
		vernet massiv putey.  rabota zavisit ot nalichiy files "booking0_FILE_UNIQ_APART_KEY_02.09.2020_20-19-55.kr4"
		algoritm perebiraer vse files v katalogah level2dir && level3dir i vozvrat znacheniy ne zavisit ot tekuchey dati
		*/
		static std::vector<std::string> get_path_for_run_utils();

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
