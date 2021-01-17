#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include <list>
#include <set>
#include <vector>
#include <map>
#include "Verify.h"
#include "Commands.h"
#include "Column.h"
#include "Table.h"

class DROP_TABLE :public Commands
{
public:
	bool isOK = false;
	string table_dropped;
	void drop_table(string comanda)
	{
		char* dp = new char[comanda.length() + 1];
		strcpy_s(dp, comanda.length() + 1, comanda.c_str());
		char* poz = NULL;
		char* next_poz = NULL;
		const char* sep = " ";
		poz = strtok_s(dp, sep, &next_poz);
		string table_name;
		int nr_cuv = 0;
		while (poz != NULL)
		{

			nr_cuv++;
			table_name = poz;
			poz = strtok_s(NULL, sep, &next_poz);

		}
		if (nr_cuv > 3)
			cout << "Wrong table name" << endl;
		else
		{
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
				if ((*it).table_name == table_name)
				{
					ok = true;
					isOK = true;
					table_dropped = table_name;
					string table_data = table_name + "_data";
					string table_structure = table_name + "_structure";
					tl.erase(it);
					remove(table_data.c_str());
					remove(table_structure.c_str());
					break;

				}
			if (ok == false)
				cout << "Table doesn't exist" << endl;

		}
	}

	void display_message() override
	{
		cout << "Table dropped";
	}

	void display_name() override
	{
		cout << table_dropped;
	}
};