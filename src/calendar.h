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

		void Init(std::vector<std::experimental::filesystem::path> level3dir);

		void Init();

		void RenderStat();

		std::vector<std::string> get_all_name_by_init_map()
		{
			std::vector<std::string> Names;
			for (auto it = _MapDataBase.GetMap().begin(); it != _MapDataBase.GetMap().end(); ++it)
			{
				Names.push_back(
					it->first
				);
			}
			return Names;
			//std::vector<std::string>
		}
			 

	private:
		Level1::CMapDataBase _MapDataBase;

	};

}




#endif /*CALENDAR_H*/