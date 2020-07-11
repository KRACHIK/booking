
#include "apartament.h"
#include "calendar_def.h"
#include "parser_impl.h"

std::string CHome::create_qniq_key() const
{
	return  GetName() + "_" + get_url_mini_img();
}

CHome CHome::Deserealize(const CStr & Str)
{
	std::vector<CStr> Arr = Str::Util::Parse_Space(Str);

	CStr Name = Arr[0];
	int Cost = std::stoi(Arr[1]);

	std::string sURL = Arr[2];

	return  CHome(Name, sURL, Cost);
}

void CHome::SaveBySelfName(const std::string & Prefix)
{
	std::string  sFileName = Prefix + _sName + "_" + std::to_string(_Cost);
	Save(sFileName);
}

void CHome::Save(const std::string & sFileName)
{
	std::stringstream ss;
	ss << "Name " << _sName << "\n";
	ss << "Cost " << _Cost << "\n";
	ss << "UrlMiniIMG " << _sUrlMiniIMG << "\n";

	std::ofstream outFile(sFileName);
	outFile << ss.rdbuf();
	outFile.close();
}

std::string CHome::GetSerialize()
{
	std::string ss = _sName + " " + std::to_string(_Cost) + " " + _sUrlMiniIMG + "\n";
	return ss;
}
