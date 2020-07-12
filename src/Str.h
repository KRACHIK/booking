#ifndef STR_H
#define STR_H

#include "calendar_def.h"

#ifdef QT_COMPILER
	// zero
#else
	#include "def.h"
#endif
 
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <regex>

// CStringFuncs
 
	class CStringFuncs
	{
	public:
		static std::vector <CStr> Parse_Space(const std::string & buf);
		 
		static std::string do_replace(const std::string & in, const std::string &from, const std::string & to);

		static dati Parse_GetDataByPath(const std::string & Src);

		static dati Parse_day_mother_year(const std::string & Src);
	};
 
 

#endif 
