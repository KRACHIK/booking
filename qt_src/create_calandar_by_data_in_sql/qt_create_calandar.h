#ifndef CREATE_CALENDAR_H
#define CREATE_CALENDAR_H
#include <string>
#include <vector>

#include "../sql_get_assoc_info_by_apart_key/sql_find_get_assoc_info.h"
#include "../sql_foreach_uniq_key/sql_foreach_uniq_key.h"
#include "../src_sql_engine/database.h"
#include "../../src/calendar_map_adapter.h"


class CGetApart
{
public:
   static void init(  );
};

#endif // CREATE_CALENDAR_H
