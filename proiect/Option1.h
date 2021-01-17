#pragma once
#include <iostream>
#include "Options.h"

class Option1 : public Options
{
public:
	void option() override
	{
		cout << "POSSIBLE COMMAND : ";
		cout << endl << "-> DISPLAY TABLE table_name ";
	}

};