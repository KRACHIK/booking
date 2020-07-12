#include <string>
#include "common.h"
#include "StringWrap.h"
#include "calendar_map_adapter.h"
 
class COneAppartStatProvider 
{
public:
	std::string GetPathToFileStat() const
	{
		return "D:\\Development\\booking\\bin2\\assoc_data.txtFILE_PROCESSING_INFO_RESULT_Alexanders&#39;SkiStudio.kr4";
	}
};

class CBuilder {
public:
	 
	  std::vector<std::string> CBuilder::deserialize_status(const std::string & sFilePatth);

};


std::vector<std::string>  CBuilder::deserialize_status(const std::string & sFilePatth)
{
	client::CAllNameFile File_(sFilePatth);
	 
	std::vector<std::string> StatusArr;
	 
	for (auto & it : File_.GetArrName())
	{
		std::vector<std::string> token = CStringFuncs3::split_Into_words(it);
		 
		StatusArr.push_back(CCalendar::GetStatus(token));
	}
		  
	return StatusArr;
}

int main( )
{
	CBuilder  Builder;
	COneAppartStatProvider  OneAppartStatProvider;

	Builder.deserialize_status(OneAppartStatProvider.GetPathToFileStat());

	return 0;
}
