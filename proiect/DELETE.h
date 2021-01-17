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

class DELETE : public Commands
{
public:
	bool isOK = false;
	string table_altered;
	void delete_from(string comanda)
	{
		string table_name;
		size_t found = comanda.find(" WHERE ");
		string c1 = comanda.substr(0, found);
		map<string, int> m = extract_table_name(c1);
		map<string, int>::iterator it = m.begin();
		if (it->second > 3)
			cout << "Wrong table name" << endl;
		else
		{
			table_name = it->first;
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;
					isOK = true;
					table_altered = table_name;
					string f_name = table_name + "_data";

					if (found != string::npos)
					{
						string c2 = comanda.substr(found + 1, comanda.length());
						map<string, string> mp = extract_condition(c2);
						map<string, string>::iterator iter = mp.begin();
						int nr = 0, poz;
						for (auto& i : (*it).column_vector)
						{
							++nr;
							if (i.name == iter->first)
								poz = nr;
						}
						int length;
						list<vector<string>> vl;
						remove(f_name.c_str());
						ofstream f(f_name, ios::binary | ios::app);
						for (auto& i : (*it).inregistrari)
						{
							if (i[poz - 1] != iter->second)
							{
								vl.push_back(i);
							}
						}

						(*it).inregistrari.clear();
						(*it).inregistrari = vl;
						for (auto& i : (*it).inregistrari)
						{
							for (auto& j : i)
							{
								cout << j << " ";
								length = j.length();
								f.write((char*)&length, sizeof(length));
								f.write(j.c_str(), length + 1);
							}
							cout << endl;
						}
						f.close();
					}
					else
					{
						(*it).inregistrari.clear();
						remove(f_name.c_str());
						ofstream f(f_name, ios::binary);
					}
				}
			}
			if (ok == false)
				cout << "Table doesn't exist" << endl;
		}
	}
	void display_message() override
	{
		cout << "Rows deleted";
	}
	void display_name() override
	{
		cout << table_altered;
	}
};