cmake_minimum_required(VERSION 2.8)  
   

project(booking_html_parser)
file( GLOB SOURCE_CODE  
	src/base.cpp
	src/base.h
	src/def.h
	src/main.cpp
	
	src/file.h
	src/file.cpp
	 
	src/parser.h
	src/parser.cpp
	
	src/parser_impl.h
	src/parser_impl.cpp

	src/common.cpp
	src/common.h


	src/base.cpp
	src/base.h
	src/def.h
	
	src/file.h
	src/file.cpp
 	
	src/common.cpp
	src/common.h

	src/fix_compilate.cpp
	src/fix_compilate.h
	   
	src/calendar_def.h
	 
	src/filesystem.h
	src/filesystem.cpp
	src/DownloadModul.cpp
	src/DownloadModul.h
	src/foreach_dir.cpp
	src/foreach_dir.h

	src/calendar_data_provider.h
	src/calendar_data_provider.cpp
	  
	src/calendar_map_adapter.h
	src/calendar_map_adapter.cpp
	  
	src/SrcContainer/BaseDequeObject.cpp
	src/SrcContainer/BaseDequeObject.h
	src/SrcContainer/EngineBaseMapObject.h

	src/parser_impl.h
	src/parser_impl.cpp

	src/Str.h
	src/Str.cpp
	
	src/Client_Base_type.h
	src/Client_Base_type.cpp
	
)
add_executable(booking_html_parser ${SOURCE_CODE})	 
#####################################################################################
   

project(main_prod_parser)
file( GLOB SOURCE_CODE  
	src/main_prod_parser.cpp 
	src/base.cpp
	src/base.h
	src/def.h
	
	src/file.h
	src/file.cpp
	  
	src/filesystem.h
	src/filesystem.cpp
	src/DownloadModul.cpp
	src/DownloadModul.h
	src/foreach_dir.cpp
	src/foreach_dir.h 

	src/common.cpp
	src/common.h
	 
	src/logic_impl.h
	src/logic_impl.cpp
	 
	src/Str.h
	src/Str.cpp
)
add_executable(main_prod_parser ${SOURCE_CODE})	 
#####################################################################################
  	 
	
	
project(get_data_ob_odnom_otele)
file( GLOB SOURCE_CODE  
	src/main_data_ob_odnom_otele.cpp 

	 
	src/base.cpp
	src/base.h

	src/def.h
	
	src/file.h
	src/file.cpp
 	
	src/common.cpp
	src/common.h
	  
	src/calendar_def.h
	 
	src/calendar.cpp
	src/calendar.h
	 
	src/filesystem.h
	src/filesystem.cpp
	src/DownloadModul.cpp
	src/DownloadModul.h
	src/foreach_dir.cpp
	src/foreach_dir.h

	src/calendar_data_provider.h
	src/calendar_data_provider.cpp
	  
	src/calendar_map_adapter.h
	src/calendar_map_adapter.cpp
	  
	src/SrcContainer/BaseDequeObject.cpp
	src/SrcContainer/BaseDequeObject.h
	src/SrcContainer/EngineBaseMapObject.h
	 
	src/fix_compilate.cpp
	src/fix_compilate.h
	  
	src/parser_impl.h
	src/parser_impl.cpp

	src/Str.h
	src/Str.cpp
	
	src/Client_Base_type.h
	src/Client_Base_type.cpp
	 
	src/def.h
	 
	src/logic_impl.h
	src/logic_impl.cpp
)
add_executable(get_data_ob_odnom_otele ${SOURCE_CODE})	 
#####################################################################################
  	



	
project(map_abrabotka)
file( GLOB SOURCE_CODE  
	src/main_map_obrabotka.cpp 

	src/base.cpp
	src/base.h
	src/def.h
	
	src/file.h
	src/file.cpp
 	 
	src/common.cpp
	src/common.h
	src/calendar_def.h
	src/calendar.cpp
	src/calendar.h
	
	src/filesystem.h
	src/filesystem.cpp
	src/foreach_dir.cpp
	src/foreach_dir.h
	src/DownloadModul.cpp
	src/DownloadModul.h

	src/calendar_data_provider.h
	src/calendar_data_provider.cpp
	src/calendar_map_adapter.h
	src/calendar_map_adapter.cpp
	src/SrcContainer/BaseDequeObject.cpp
	src/SrcContainer/BaseDequeObject.h
	src/SrcContainer/EngineBaseMapObject.h
	src/fix_compilate.cpp
	src/fix_compilate.h
	src/parser_impl.h
	src/parser_impl.cpp
	src/Str.h
	src/Str.cpp
	src/Client_Base_type.h
	src/Client_Base_type.cpp
	src/logic_impl.h 
	src/logic_impl.cpp
)
add_executable(map_abrabotka ${SOURCE_CODE})	 
#####################################################################################
  	

project(render_info_by_one_appart)
file( GLOB SOURCE_CODE  
	src/render_info_by_one_appart.cpp 

	src/base.cpp
	src/base.h
	src/def.h
	
	src/file.h
	src/file.cpp
 	 
	src/common.cpp
	src/common.h
	src/calendar_def.h
	src/calendar.cpp
	src/calendar.h

	src/foreach_dir.cpp
	src/foreach_dir.h
	src/DownloadModul.cpp
	src/DownloadModul.h
	src/filesystem.h
	src/filesystem.cpp
	

	src/calendar_data_provider.h
	src/calendar_data_provider.cpp
	src/calendar_map_adapter.h
	src/calendar_map_adapter.cpp
	src/SrcContainer/BaseDequeObject.cpp
	src/SrcContainer/BaseDequeObject.h
	src/SrcContainer/EngineBaseMapObject.h
	src/fix_compilate.cpp
	src/fix_compilate.h
	src/parser_impl.h
	src/parser_impl.cpp
	src/Str.h
	src/Str.cpp
	src/Client_Base_type.h
	src/Client_Base_type.cpp
	src/logic_impl.h 
	src/logic_impl.cpp
	src/StringWrap.h
	src/StringWrap.cpp
)
add_executable(render_info_by_one_appart ${SOURCE_CODE})	 
#####################################################################################
  	


project(add_uniq_key_to_sql_bd)
file( GLOB SOURCE_CODE  
	src/add_uniq_key_to_sql_bd.cpp 

	src/base.cpp
	src/base.h
	src/def.h
	
	src/file.h
	src/file.cpp
 	 
	src/common.cpp
	src/common.h
	src/calendar_def.h
	src/calendar.cpp
	src/calendar.h
	
	src/filesystem.h
	src/filesystem.cpp
	src/foreach_dir.cpp
	src/foreach_dir.h
	src/DownloadModul.cpp
	src/DownloadModul.h

	src/calendar_data_provider.h
	src/calendar_data_provider.cpp
	src/calendar_map_adapter.h
	src/calendar_map_adapter.cpp
	src/SrcContainer/BaseDequeObject.cpp
	src/SrcContainer/BaseDequeObject.h
	src/SrcContainer/EngineBaseMapObject.h
	src/fix_compilate.cpp
	src/fix_compilate.h
	src/parser_impl.h
	src/parser_impl.cpp
	src/Str.h
	src/Str.cpp
	src/Client_Base_type.h
	src/Client_Base_type.cpp
	src/logic_impl.h 
	src/logic_impl.cpp
)
add_executable(add_uniq_key_to_sql_bd ${SOURCE_CODE})	 
#####################################################################################

project(create_calendar_by_asscoc_vector)
file( GLOB SOURCE_CODE  
	src/create_calendar_by_asscoc_vector.cpp 

	src/base.cpp
	src/base.h
	src/def.h
	
	src/file.h
	src/file.cpp
 	 
	src/common.cpp
	src/common.h
	src/calendar_def.h
	src/calendar.cpp
	src/calendar.h
	
	src/filesystem.h
	src/filesystem.cpp
	src/foreach_dir.cpp
	src/foreach_dir.h
	src/DownloadModul.cpp
	src/DownloadModul.h

	src/calendar_data_provider.h
	src/calendar_data_provider.cpp
	src/calendar_map_adapter.h
	src/calendar_map_adapter.cpp
	src/SrcContainer/BaseDequeObject.cpp
	src/SrcContainer/BaseDequeObject.h
	src/SrcContainer/EngineBaseMapObject.h
	src/fix_compilate.cpp
	src/fix_compilate.h
	src/parser_impl.h
	src/parser_impl.cpp
	src/Str.h
	src/Str.cpp
	src/Client_Base_type.h
	src/Client_Base_type.cpp
	src/logic_impl.h 
	src/logic_impl.cpp
)
add_executable(create_calendar_by_asscoc_vector ${SOURCE_CODE})	 
#####################################################################################
  	

project(TotalHome_parser)
file( GLOB SOURCE_CODE  
  	src/base.cpp
	src/base.h
	src/def.h
	src/MainTotalHome_parser.cpp
	src/file.h
	src/file.cpp
	src/parser.h
	src/parser.cpp
	src/parser_impl.h
	src/parser_impl.cpp
	src/common.cpp
	src/common.h
	src/base.cpp
	src/base.h
	src/def.h
	src/common.cpp
	src/common.h
	src/fix_compilate.cpp
	src/fix_compilate.h
	src/calendar_def.h
	
	src/filesystem.h
	src/filesystem.cpp 
	src/foreach_dir.cpp
	src/foreach_dir.h
	src/DownloadModul.cpp
	src/DownloadModul.h

	src/calendar_data_provider.h
	src/calendar_data_provider.cpp
	src/calendar_map_adapter.h
	src/calendar_map_adapter.cpp
	src/SrcContainer/BaseDequeObject.cpp
	src/SrcContainer/BaseDequeObject.h
	src/SrcContainer/EngineBaseMapObject.h
	src/parser_impl.h
	src/parser_impl.cpp
	src/Str.h
	src/Str.cpp
	src/Client_Base_type.h
	src/Client_Base_type.cpp
	
) 
add_executable(TotalHome_parser ${SOURCE_CODE})	 
#####################################################################################
   
   
   
project(asunk_task_wrap)
file( GLOB SOURCE_CODE2 
	src/thread_simple.cpp
	 
	src/src_thread/wrap_thread.h
	src/src_thread/wrap_thread.cpp
)
add_executable(asunk_task_wrap ${SOURCE_CODE2})	 
#####################################################################################
	  

   
project(logic)
file( GLOB SOURCE_CODE2 
	src/logic.cpp

src/logic_impl.h 
src/logic_impl.cpp
src/base.cpp
src/base.h
src/def.h
src/file.h
src/file.cpp
src/common.cpp
src/common.h
src/calendar_def.h
src/calendar.cpp
src/calendar.h
src/filesystem.h
src/filesystem.cpp
src/DownloadModul.cpp
src/DownloadModul.h
src/foreach_dir.cpp
src/foreach_dir.h
src/calendar_data_provider.h
src/calendar_data_provider.cpp
src/calendar_map_adapter.h
src/calendar_map_adapter.cpp
src/SrcContainer/BaseDequeObject.cpp
src/SrcContainer/BaseDequeObject.h
src/SrcContainer/EngineBaseMapObject.h
src/fix_compilate.cpp
src/fix_compilate.h
src/parser_impl.h
src/parser_impl.cpp
src/Str.h
src/Str.cpp
src/Client_Base_type.h
src/Client_Base_type.cpp
 
	 
)
add_executable(logic ${SOURCE_CODE2})	 
#####################################################################################

project(MainOnlyDownloadManager)
file( GLOB SOURCE_CODE2 
	src/base.cpp
	src/base.h
	src/def.h
	
	src/file.h
	src/file.cpp
	src/MainOnlyDownloadManager.cpp
	
	src/filesystem.h
	src/filesystem.cpp
	src/DownloadModul.cpp
	src/DownloadModul.h
	src/foreach_dir.cpp
	src/foreach_dir.h
	 
	src/common.cpp
	src/common.h
	 
	src/logic_impl.h
	src/logic_impl.cpp
	 
	src/Str.h
	src/Str.cpp
)
	
add_executable(MainOnlyDownloadManager ${SOURCE_CODE2})	 
#####################################################################################

	 
	 
	 
project(MainDownloadManagerByFileList)
file( GLOB SOURCE_CODE2 
	src/base.cpp
	src/base.h
	src/def.h
	src/file.h
	src/file.cpp
	src//MainDownloadManagerByFileList.cpp
	
	src/filesystem.h
	src/filesystem.cpp
	src/DownloadModul.cpp
	src/DownloadModul.h
	src/foreach_dir.cpp
	src/foreach_dir.h
	
	src/common.cpp
	src/common.h
	src/logic_impl.h
	src/logic_impl.cpp
	src/Str.h
	src/Str.cpp
)
	
add_executable(MainDownloadManagerByFileList ${SOURCE_CODE2})	 
#####################################################################################


project(calendar)
file( GLOB SOURCE_CODE2 
	src/base.cpp
	src/base.h
	src/def.h
	
	src/file.h
	src/file.cpp
 	
	src/common.cpp
	src/common.h
	  
	src/calendar_def.h

	src/calendar_main.cpp

	src/calendar.cpp
	src/calendar.h
	 
	
	src/filesystem.h
	src/filesystem.cpp
	src/foreach_dir.cpp
	src/foreach_dir.h
	src/DownloadModul.cpp
	src/DownloadModul.h

	src/calendar_data_provider.h
	src/calendar_data_provider.cpp
	  
	src/calendar_map_adapter.h
	src/calendar_map_adapter.cpp
	  
	src/SrcContainer/BaseDequeObject.cpp
	src/SrcContainer/BaseDequeObject.h
	src/SrcContainer/EngineBaseMapObject.h
	 
	src/fix_compilate.cpp
	src/fix_compilate.h
	  
	src/parser_impl.h
	src/parser_impl.cpp

	src/Str.h
	src/Str.cpp
	
	src/Client_Base_type.h
	src/Client_Base_type.cpp
  
)
add_executable(calendar ${SOURCE_CODE2})	 
#####################################################################################


project(add_sql_full_raw_info_by_appart)
file( GLOB SOURCE_CODE2 
	src/add_sql_full_raw_info_by_appart.cpp
	          
src/filesystem.h
src/filesystem.cpp
src/DownloadModul.cpp
src/DownloadModul.h
src/foreach_dir.cpp
src/foreach_dir.h

src/logic_impl.h 
src/logic_impl.cpp
src/base.cpp
src/base.h
src/def.h
src/file.h
src/file.cpp
src/common.cpp
src/common.h
src/calendar_def.h
src/calendar.cpp
src/calendar.h
src/calendar_data_provider.h
src/calendar_data_provider.cpp
src/calendar_map_adapter.h
src/calendar_map_adapter.cpp
src/SrcContainer/BaseDequeObject.cpp
src/SrcContainer/BaseDequeObject.h
src/SrcContainer/EngineBaseMapObject.h
src/fix_compilate.cpp
src/fix_compilate.h
src/parser_impl.h
src/parser_impl.cpp
src/Str.h
src/Str.cpp
src/Client_Base_type.h
src/Client_Base_type.cpp
 
  
)
add_executable(add_sql_full_raw_info_by_appart ${SOURCE_CODE2})	 
#####################################################################################
     
   
project(prod)