#ifndef DOWNLOAD_MODUL_H
#define DOWNLOAD_MODUL_H

#include "common.h"
#include "Str.h"
#include "base.h"



#include <iostream>
#include <string>
#include <regex>

class CDownload
{

public:

	static bool IsPropuskDwnFile(const std::string & sDir)
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


};


#endif /*DOWNLOAD_MODUL_H*/