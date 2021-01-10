#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Commands.h"
using namespace std;

class Verify {

public:
	Commands c;
	void file(string file_name)
	{
		ifstream f(file_name);
		if (f.is_open())
		{
			string comanda;
			while (getline(f, comanda))
				check(comanda);
		}
	}

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

		found = comanda.find("SELECT");
		found1 = comanda.find("ALL");
		size_t found2 = comanda.find("WHERE");
		if (found != string::npos && found1 != string::npos && found2 != string::npos)
			c.select_all_where(comanda);
		else
		{
			if (found != string::npos && found1 != string::npos)
				c.select_all(comanda);
			else {
				if (found != string::npos && found2 != string::npos)
					c.select_where(comanda);
				else
					if (found != string::npos)
						c.select(comanda);
			}
		}
		found = comanda.find("UPDATE");
		found1 = comanda.find("SET");
		found2 = comanda.find("WHERE");
		if (found != string::npos && found1 != string::npos && found2 != string::npos)
			c.update(comanda);


	}
};