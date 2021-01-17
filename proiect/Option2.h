#pragma once
#include <iostream>
#include "Options.h"

class Option2 :public Options
{
public:
	void option() override
	{
		cout << "POSSIBLE COMMANDS : ";
		cout << endl << "-> SELECT ALL FROM table_name";
		cout << endl << "-> SELECT ALL FROM table_name WHERE column=value";
		cout << endl << "-> SELECT column1, column2,...FROM table_name";
		cout << endl << "-> SELECT column1, column2,...FROM table_name WHERE column=value ";
	}
};