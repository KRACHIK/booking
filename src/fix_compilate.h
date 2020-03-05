#ifndef FIX_COMPILATE_H
#define FIX_COMPILATE_H

#include "def.h"
 
class CHome
{
public:

	CHome() { }

	CHome(const std::string & Name, int Cost) : _sName(Name), _Cost(Cost) { }


	static CHome Deserealize(const CStr & Str);
	void SaveBySelfName(const std::string & Prefix);
	void Save(const std::string & sFileName);
	std::string GetSerialize();

	std::string GetName() { return _sName; }
	int  GetCost() { return _Cost; }


private:
	std::string  _sName;
	int _Cost;
};


#endif /*CALENDAR_H*/