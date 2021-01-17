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

class INSERT :public Commands
{
public:
	bool isOK = false;
	string table_altered;
	void insert(string comanda)
	{
		vector<string> v;
		string table_name;
		string c1;
		string c2;
		char* cf1;
		char* cf2;
		size_t found = comanda.find("VALUES");
		if (found != string::npos)
		{
			c1 = comanda.substr(0, found);
			c2 = comanda.substr(found, comanda.length());
			cf1 = new char[c1.length() + 1];
			strcpy_s(cf1, c1.length() + 1, c1.c_str());
			cf2 = new char[c2.length() + 1];
			strcpy_s(cf2, c2.length() + 1, c2.c_str());
			char* poz = NULL;
			char* next_poz = NULL;
			poz = strtok_s(cf1, " ", &next_poz);
			int nr_cuv = 0;
			int nr = 0;
			while (poz != NULL && nr <= 3)
			{
				nr++;
				table_name = poz;
				poz = strtok_s(NULL, " ", &next_poz);
			}
			if (nr_cuv > 3)
			{
				cout << "Wrong table name" << endl;
			}

			else
			{

				bool ok = false;//presupunem ca nu exista o tabela cu acest nume
				for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
				{
					if ((*it).table_name == table_name)
					{
						ok = true;
						isOK = true;
						table_altered = table_name;
						string table_data = table_name + "_data";
						ofstream f(table_data, ios::binary | ios::app);
						size_t found = comanda.find("(");
						poz = NULL;
						next_poz = NULL;

						poz = strtok_s(cf2 + 6, "(,) ", &next_poz);
						int length;
						vector<string> linie;
						while (poz != NULL)
						{

							char* poz1;
							if (strchr(poz, '"') != NULL)
							{
								poz1 = poz + 1;
								poz1[strlen(poz1) - 1] = '\0';
								poz = poz1;
							}
							length = strlen(poz);
							f.write((char*)&length, sizeof(length));
							f.write(poz, length + 1);
							linie.push_back(poz);
							poz = strtok_s(NULL, "(,)", &next_poz);
						}

						(*it).inregistrari.push_back(linie);
						f.close();
					}
				}
				if (ok == false)
					cout << "Table doesn't exist" << endl;
			}
		}
		else
			cout << "missing VALUES keyword" << endl;
	}

	void insert_csv(string comanda)
	{
		string table_name;
		string csv_file;
		char* c_file = new char[comanda.length() + 1];
		strcpy_s(c_file, comanda.length() + 1, comanda.c_str());
		char* poz = NULL;
		char* next_poz = NULL;
		poz = strtok_s(c_file, " ", &next_poz);
		int nr_cuv = 0;
		int nr = 0;
		while (poz != NULL && nr < 3)
		{
			nr++;
			if (nr == 2)
			{
				table_name = poz;
			}
			if (nr == 3)
			{
				csv_file = poz;
			}
			poz = strtok_s(NULL, " ", &next_poz);
		}
		if (poz != NULL)
		{
			cout << "Wrong table name or wrong file name" << endl;
		}
		else
		{

			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					isOK = true;
					ok = true;
					table_altered = table_name;
					string table_data = table_name + "_data";
					ofstream f(table_data, ios::binary | ios::app);
					fstream fcsv;
					fcsv.open(csv_file, ios::in);
					string  line;
					char* poz;
					char* next_poz;
					while (getline(fcsv, line))
					{
						vector<string> linie;
						/*cout << line << endl;*/
						poz = NULL;
						next_poz = NULL;
						char* ch_line = new char[line.length() + 1];
						strcpy_s(ch_line, line.length() + 1, line.c_str());
						poz = strtok_s(ch_line, ",", &next_poz);
						while (poz != NULL)
						{
							char* c;
							if (poz[0] == ' ')
							{
								c = poz + 1;
								poz = c;
							}
							int length = strlen(poz);
							f.write((char*)&length, sizeof(length));
							f.write(poz, length + 1);
							linie.push_back(poz);
							poz = strtok_s(NULL, ",", &next_poz);

						}
						delete[] ch_line;
						(*it).inregistrari.push_back(linie);
					}
				}

			}
		}
	}

	void display_message() override
	{

		cout << "Values inserted";
	}

	void display_name() override
	{
		cout << table_altered;
	}
};