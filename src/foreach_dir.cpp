
#include "foreach_dir.h"

std::vector<std::experimental::filesystem::path>
CPathFuncs::get_all_level3_dir(CDownLoadList & DownLoadList
	, std::vector<std::experimental::filesystem::path> level2dir
	, client::CSeting  & Seting)
{
	/*-------D:\Development\booking\bin2\Debug\db\-2326178\08.03.2020\09.03.2020-11.03.2020
	----------------------------------------------Levle-1----Levle-2---------Levle-3   */

	std::vector<std::experimental::filesystem::path> ArrIntrestingDir;


	for (auto it : level2dir)
	{
		std::vector<std::experimental::filesystem::path> arrDir = CFileSystem::directory_iterator(it.string());

		for (auto j : arrDir)
		{
			std::string dir(j.string(), it.string().size());
			int sfd;

			if (dir.size() == 22)
				ArrIntrestingDir.push_back(j);
		}
	}


	return ArrIntrestingDir;
}



 

 std::vector<std::experimental::filesystem::path> CPathFuncs::get_all_level3_dir__(CDownLoadList & DownLoadList
	, std::vector<std::string> level2dir, client::CSeting  & Seting)
{
	/*-------D:\Development\booking\bin2\Debug\db\-2326178\08.03.2020\09.03.2020-11.03.2020
	----------------------------------------------Levle-1----Levle-2---------Levle-3   */

	std::vector<std::experimental::filesystem::path> ArrIntrestingDir;


	for (auto it : level2dir)
	{
		std::vector<std::experimental::filesystem::path> arrDir = CFileSystem::directory_iterator(it );

		for (auto j : arrDir)
		{
			std::string dir(j.string(), it.size());
			int sfd;

			if (dir.size() == 22)
				ArrIntrestingDir.push_back(j);
		}
	}


	return ArrIntrestingDir;
}



std::vector<std::string> CPathFuncs::get_all_level1_dir(CDownLoadList & DownLoadList, client::CSeting  & Seting)
{
	/*-------D:\Development\booking\bin2\Debug\db\-2326178\08.03.2020\09.03.2020-11.03.2020
	----------------------------------------------Levle-1----Levle-2---------Levle-3   */

	std::vector<std::string> arrDir;
	// Xodit po stranam
	for (auto it : DownLoadList.get_valid_link())
	{

		// set current country for setting object
		std::string  sCountryIndex;
		bool bRet = DownLoadList.get_dest_by_link(it, sCountryIndex);
		Seting.set_work_country_dir(sCountryIndex);
		Seting.set_country(sCountryIndex);

		std::string ActualWorkDir = Seting.GetWorkDir(); //D:\Development\booking\bin2\Debug\db\-2327363
		arrDir.push_back(ActualWorkDir);

	}

	return arrDir;
}


std::vector<std::experimental::filesystem::path> CPathFuncs::get_all_level2_dir(CDownLoadList & DownLoadList, client::CSeting  & Seting)
{
	/*-------D:\Development\booking\bin2\Debug\db\-2326178\08.03.2020\09.03.2020-11.03.2020
	----------------------------------------------Levle-1----Levle-2---------Levle-3   */

	std::vector<std::experimental::filesystem::path> Ret;

	// Xodit po stranam
	for (auto it : DownLoadList.get_valid_link())
	{

		// set current country for setting object
		std::string  sCountryIndex;
		bool bRet = DownLoadList.get_dest_by_link(it, sCountryIndex);
		Seting.set_work_country_dir(sCountryIndex);
		Seting.set_country(sCountryIndex);

		std::string ActualWorkDir = Seting.GetWorkDir(); //D:\Development\booking\bin2\Debug\db\-2327363

		std::vector<std::experimental::filesystem::path> arrDir = CFileSystem::directory_iterator(ActualWorkDir);

		///filter get only tru dir
		for (auto t : arrDir)
		{
			std::string tru = std::string(t.string(), ActualWorkDir.size());

			if (tru.size() != 11) // target ---------------> "/08.03.2020"
			{
				continue;
			}
			else
			{
				//grab
				Ret.push_back(t);
			}
		}

	}

	return Ret;
}

std::vector<std::string> CWrapPath::get_all_level1_dir(CDownLoadList & DownLoadList, client::CSeting & Seting)
{
	std::vector<std::string> ret = CPathFuncs::get_all_level1_dir(DownLoadList, Seting);
	return ret;
}

  std::vector<std::string> CWrapPath::get_all_level2_dir(CDownLoadList & DownLoadList, client::CSeting & Seting)
{
	std::vector<std::experimental::filesystem::path> tmp = CPathFuncs::get_all_level2_dir(DownLoadList, Seting);
	std::vector<std::string> ret;

	for (std::experimental::filesystem::path it : tmp)
	{
		ret.push_back(it.string());
	}

	return ret;
}
  
 std::vector<std::string> CWrapPath::get_all_level3_dir(CDownLoadList & DownLoadList
	, std::vector<std::string> level2dir, client::CSeting & Seting)
{
	std::vector<std::experimental::filesystem::path> tmp = CPathFuncs::get_all_level3_dir__(DownLoadList, level2dir, Seting);
 	
	std::vector<std::string> ret;

	for (std::experimental::filesystem::path it : tmp)
	{
		ret.push_back(it.string());
	}

	return ret; 
	 
	//return { "" };
}

