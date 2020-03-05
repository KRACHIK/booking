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
   
   
project(logic)
file( GLOB SOURCE_CODE2 
	src/base.cpp
	src/base.h
	src/def.h
	
	src/file.h
	src/file.cpp

	src/logic.cpp
	
	src/DownloadModul.cpp
	src/DownloadModul.h

	src/common.cpp
	src/common.h
	 
	src/logic_impl.h
	src/logic_impl.cpp
	 
	src/Str.h
	src/Str.cpp
	
)
add_executable(logic ${SOURCE_CODE2})	 
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
add_executable(calendar ${SOURCE_CODE2})	 
#####################################################################################
   
   
project(prod)