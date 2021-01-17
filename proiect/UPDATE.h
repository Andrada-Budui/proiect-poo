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

class UPDATE : public Commands
{
public:
	bool isOK = false;
	string table_updated;
	void update(string comanda)
	{
		string table_name;
		string setCol, setVal;
		string whereCol, whereVal;

		size_t found = comanda.find("SET ");
		string c1 = comanda.substr(0, found);
		string c11 = comanda.substr(found, comanda.length());
		size_t found1 = c11.find("WHERE ");
		string c2 = c11.substr(0, found1);
		string c3 = c11.substr(found1, c11.length());


		char* cf1 = new char[c1.length() + 1];
		strcpy_s(cf1, c1.length() + 1, c1.c_str());
		char* cf2 = new char[c2.length() + 1];
		strcpy_s(cf2, c2.length() + 1, c2.c_str());
		char* cf3 = new char[c3.length() + 1];
		strcpy_s(cf3, c3.length() + 1, c3.c_str());

		//extragere nume tabela
		char* poz = NULL;
		char* next_poz = NULL;
		poz = strtok_s(cf1, " ", &next_poz);
		poz = strtok_s(NULL, " ", &next_poz);
		table_name = poz;

		//extragere conditie SET
		poz = NULL;
		next_poz = NULL;
		poz = strtok_s(cf2 + 4, "=", &next_poz);
		setCol = poz;
		poz = strtok_s(NULL, "=", &next_poz);
		setVal = poz;

		//extragere conditie where
		poz = NULL;
		next_poz = NULL;
		poz = strtok_s(cf3 + 6, "=", &next_poz);
		whereCol = poz;
		poz = strtok_s(NULL, "=", &next_poz);
		whereVal = poz;


		bool ok = false;//presupunem ca nu exista tabela
		for (auto it = tl.begin(); it != tl.end(); ++it)
		{
			if ((*it).table_name == table_name)
			{
				isOK = true;
				ok = true;
				table_updated = table_name;
				int poz_set, poz_where, nr = 0;
				for (auto& i : (*it).column_vector)
				{
					nr++;
					if (i.name == setCol)
						poz_set = nr;
					if (i.name == whereCol)
						poz_where = nr;
				}

				for (auto& i : (*it).inregistrari)
				{

					if (i[poz_where - 1] == whereVal)
						i[poz_set - 1] = setVal;
				}
				string f_name = table_name + "_data";
				int length;
				remove(f_name.c_str());
				ofstream f(f_name, ios::binary | ios::app);
				for (auto& i : (*it).inregistrari)
				{
					for (auto& j : i)
					{
						length = j.length();
						f.write((char*)&length, sizeof(length));
						f.write(j.c_str(), length + 1);
					}
				}

				f.close();
			}
		}
		if (!ok)
			cout << "Table doesn't exist" << endl;

	}

	void display_message() override
	{
		cout << "Rows updated";
	}

	void display_name() override
	{
		cout << table_updated;
	}

};