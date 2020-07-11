#ifndef CALENDAR_H
#define CALENDAR_H

#include "common.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "foreach_dir.h"
#include "calendar_data_provider.h"
#include "calendar_map_adapter.h"

#include "calendar_def.h"

namespace client {

	class IDataBase
	{
	public:
		void create_db_for_vital();
		 
		void Init_all_name(std::vector<std::string> level3dir);

		void Write_All_Hotel_to_db(std::vector<std::string> level3dir);

		void Serialize(CHomeNameAndCostAndData Hotel);

		void Deserealize(std::string sFilePatth);
		  
		void Init_and_dolgi_obschet_raboti_kajdogo_otel9(std::vector<std::string> level3dir);

		void Init();

		void RenderStat();

		std::vector<std::string> get_all_name_by_init_map();
			 

	private:
		Level1::CMapDataBase _MapDataBase;

	};



}




#endif /*CALENDAR_H*/