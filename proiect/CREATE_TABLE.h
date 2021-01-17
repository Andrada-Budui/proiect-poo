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


class CREATE_TABLE :public Commands
{
public:
	bool isOK = false;
	string new_table;
	void create_table(string comanda)
	{
		Table tb;
		vector<string> v;
		string table_name;
		string c1;
		string c2;
		char* cf1;
		char* cf2;
		size_t found = comanda.find("(");
		if (found != string::npos)
		{
			c1 = comanda.substr(0, found);
			c2 = comanda.substr(found + 1, comanda.length());
			cf1 = new char[c1.length() + 1];
			strcpy_s(cf1, c1.length() + 1, c1.c_str());
			cf2 = new char[c2.length() + 1];
			strcpy_s(cf2, c2.length() + 1, c2.c_str());

			char* poz = NULL;
			char* next_poz = NULL;
			poz = strtok_s(cf1, " ", &next_poz);
			int nr = 0;
			while (poz != NULL && nr <= 3)
			{
				nr++;
				table_name = poz;
				poz = strtok_s(NULL, " ", &next_poz);
			}

			if (nr > 3)
				cout << "wrong table name" << endl;
			else
			{
				if (!isValid(table_name))
					cout << "wrong table name" << endl;
				else
				{
					new_table = table_name;
					tb.table_name = table_name;
					bool ok = false;//presupunem ca nu exista o tabela cu acest nume
					for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
						if ((*it).table_name == table_name)
						{
							ok = true;
							cout << "Table already exists" << endl;
						}

					if (ok == false)
					{   //extragere date
						isOK = true;
						ofstream g(table_name);
						file_name.insert(table_name);
						const char* chr = "( ,)";
						poz = NULL;
						next_poz = NULL;
						poz = strtok_s(cf2, chr, &next_poz);
						while (poz != NULL)
						{

							v.push_back(poz);
							poz = strtok_s(NULL, chr, &next_poz);
						}
						vector<Column> vc;
						vector<string>::iterator i = v.begin();
						bool valid_data = true;
						while (i != v.end() && valid_data)
						{
							Column c;
							c.name = *i;
							if (!isValid(c.name))
								valid_data = false;
							++i;

							c.type = *i;
							if (!validType(c.type))
								valid_data = false;
							++i;

							c.dimension = *i;
							int dimension;
							if (!isInteger(c.dimension))
								valid_data = false;
							else
							{
								dimension = stoi(c.dimension);
							}

							++i;
							c.defaultValue = *i;
							++i;

							if (c.type == "integer")
							{
								if (isInteger(c.defaultValue) && valid_data)
								{
									int default_value = stoi(c.defaultValue);
									g << c.name << "\t\t";
									g << c.type << "\t\t";
									g << dimension << "\t\t";
									g << default_value << "\t\t";
								}
								else
									valid_data = false;
							}

							if (c.type == "float")
							{
								if (isFloat(c.defaultValue) && valid_data)
								{
									float default_fvalue = stof(c.defaultValue);
									g << c.name << "\t\t";
									g << c.type << "\t\t";
									g << dimension << "\t\t";
									g << default_fvalue << "\t\t";
								}
								else valid_data = false;
							}
							if (c.type == "text")
							{
								if (valid_data)
								{
									g << c.name << "\t\t";
									g << c.type << "\t\t";
									g << dimension << "\t\t";
									g << c.defaultValue << "\t\t";
								}
							}
							if (!valid_data)
								cout << "No valid data";
							else
							{
								vc.push_back(c);
								g << endl;
							}
						}
						tb.column_vector = vc;
						tl.push_back(tb);
						g.close();

					}
				}
			}
		}
	}
	void display_message() override
	{

		cout << "Table created";
	}

	void display_name() override
	{
		cout << new_table;
	}

};