cmake_minimum_required(VERSION 2.8)  
   
project(booking_html_parser)
file( GLOB SOURCE_CODE  
	src/base.cpp
	src/base.h
	src/def.h
	src/main.cpp
	
	src/file.h
	src/file.cpp

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
	
	src/common.cpp
	src/common.h
	 
	src/logic_impl.h
	src/logic_impl.cpp
)
add_executable(logic ${SOURCE_CODE2})	 
#####################################################################################
   
   
project(prod)