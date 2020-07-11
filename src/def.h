#ifndef DEF_H
#define DEF_H

#include <iostream>
#include <assert.h>
 
#include <iomanip>
 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

#ifdef QT_COMPILER
	// zero
#else
	#include "file.h"
	#include "filesystem.h"
#endif  


#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <functional>
#include <algorithm>
#include <stdint.h>
#include <iterator>
#include <map> 
#include <deque>
  
#define DBG_PARSER_LOG 0

#endif  /*DEF_H*/
