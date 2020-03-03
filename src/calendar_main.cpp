#include "calendar.h"
#include <iostream>


int main()
{
	std::cout << " dsd\n";

	client::IDataBase db;
	
	db.Init();
	db.RenderStat();

	return 0;
}