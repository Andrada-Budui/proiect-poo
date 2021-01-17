#pragma once
#include <iostream>
#include "Options.h"

class Option3 :public Options
{
public:
	void option() override
	{
		cout << "POSSIBLE COMMANDS : ";
		cout << endl << "-> DELETE FROM table_name";
		cout << endl << "-> DELETE FROM table_name WHERE column=value";
		cout << endl << "-> UPDATE table_name SET column=value WHERE column1=value1";
	}
};