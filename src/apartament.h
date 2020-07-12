#ifndef FIX_COMPILATE_H
#define FIX_COMPILATE_H

#include "def.h"

class CHome
{
public:

	CHome() { }

	CHome(
		const std::string Name
		, const std::string sUrlMiniIMG
		, int Cost)
		: _sName(Name)
		, _sUrlMiniIMG(sUrlMiniIMG)
		, _Cost(Cost)
	{
	}

	std::string create_qniq_key() const;

    static CHome Deserealize(const std::string & Str);
	void SaveBySelfName(const std::string & Prefix);
	void Save(const std::string & sFileName);
	std::string GetSerialize();

	std::string GetName() const { return _sName; }
	int  GetCost() { return _Cost; }

	std::string get_url_mini_img() const { return _sUrlMiniIMG; }

private:
	std::string  _sName;
	std::string _sUrlMiniIMG;
	int _Cost;
};


#endif /*CALENDAR_H*/
