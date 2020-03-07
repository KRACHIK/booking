#ifndef DOWNLOAD_MODUL_H
#define DOWNLOAD_MODUL_H

#include "common.h"
#include "Str.h"
#include "base.h"



#include <iostream>
#include <string>
#include <regex>

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
}
 
class CDownload
{

public:
	 
	static bool VozobnovitPrervonuizagruzku(client::CSeting Seting);

	static bool IsPropuskDwnFile(const std::string & sDir, std::vector<client::CTask> & TaskArr);
	 

};


#endif /*DOWNLOAD_MODUL_H*/