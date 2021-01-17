#pragma once
#include <iostream>
#include "Options.h"

class Option4 :public Options
{
public:

	string file_name;
	void option() override
	{
		cout << "FILE NAME : ";
	}
};