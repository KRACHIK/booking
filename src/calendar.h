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
		void Init()
			;

		void RenderStat()
			;

	private:
		Level1::CMapDataBase _MapDataBase;

	};

}




#endif /*CALENDAR_H*/