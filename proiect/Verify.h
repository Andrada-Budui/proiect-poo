#pragma once
#include <iostream>
#include <string>
#include "Commands.h"
using namespace std;

class Verify {

public:
	Commands c;
	void check(string comanda)
	{

		size_t found = comanda.find("CREATE TABLE");
		if (found != string::npos)
			c.create_table(comanda);

		found = comanda.find("DROP TABLE");
		if (found != string::npos)
		{
			c.drop_table(comanda);
		}

		found = comanda.find("INSERT INTO");
		size_t found1 = comanda.find("VALUES");
		if (found != string::npos && found1 != string::npos)
		{
			c.insert(comanda);
		}

		found = comanda.find("DISPLAY TABLE");
		if (found != string::npos)
		{
			c.display_table(comanda);
		}

		found = comanda.find("DELETE");
		found1 = comanda.find("WHERE");
		if (found != string::npos && found1 != string::npos)
		{
			c.delete_w(comanda);
		}
		else if (found != string::npos)
		{
			c.delete_f(comanda);
		}



		//found = s.find("SELECT");
		//if (found != string::npos)
		//	c.create_table();

		//found = s.find("UPDATE");
		//if (found != string::npos)
		//	c.create_table();*/

	}
};