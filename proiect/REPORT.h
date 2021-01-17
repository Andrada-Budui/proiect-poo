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

class REPORT :public Commands
{
public:
	string report_name;
	bool isOK = false;
	void display_table(string comanda)
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

			table_name = poz;
			nr_cuv++;
			poz = strtok_s(NULL, sep, &next_poz);

		}
		if (nr_cuv > 3)
			cout << "Wrong table name" << endl;
		else
		{
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;
					isOK = true;
					int nr_f = 0;
					string new_file = table_name;
					for (auto& i : file_name)
					{
						size_t found = i.find(table_name);
						if (found != string::npos)
							nr_f++;
						if (nr_f != 0)
							new_file = table_name + to_string(nr_f);

					}
					file_name.insert(new_file);
					report_name = new_file;
					ofstream f(new_file);

					vector<string>column_type;
					for (auto& i : (*it).column_vector)
					{
						f << i.name << "\t\t\t";
						column_type.push_back(i.type);
					}
					f << endl;

					for (auto& i : (*it).inregistrari)
					{
						int nr = 0;
						for (auto& j : i)
						{

							if (column_type[nr] == "integer")
							{
								int newVal = stoi(j);
								cout << newVal << "\t\t\t";
								f << newVal << "\t\t\t";
							}
							else
							{
								if (column_type[nr] == "float")
								{
									float newVal1 = stof(j);
									cout << newVal1 << "\t\t\t";
									f << newVal1 << "\t\t\t";
								}
								else
								{
									cout << j << "\t\t\t\t";
									f << j << "\t\t\t\t";
								}
							}
							nr++;
						}
						cout << endl;
						f << endl;
					}
					cout << endl << endl;
				}
			}
			if (ok == false)
				cout << "Table doesn't exist" << endl;
		}
	}
	void select_all(string comanda)
	{
		string table_name;
		size_t found = comanda.find(" WHERE ");
		string c1 = comanda.substr(0, found);
		map<string, int> m = extract_table_name(c1);
		map<string, int>::iterator it = m.begin();
		if (it->second > 4)
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
					int nr_f = 0;
					string new_file = table_name;
					for (auto& i : file_name)
					{
						size_t found = i.find(table_name);
						if (found != string::npos)
							nr_f++;
						if (nr_f != 0)
							new_file = table_name + to_string(nr_f);
					}
					report_name = new_file;
					file_name.insert(new_file);
					ofstream f(new_file);
					vector<string>column_type;
					if (found == string::npos)
					{
						for (auto& i : (*it).column_vector)
						{
							f << i.name << "\t\t\t";
							column_type.push_back(i.type);
						}
						f << endl;

						for (auto& i : (*it).inregistrari)
						{
							int nr = 0;
							for (auto& j : i)
							{
								nr++;
								if (column_type[nr - 1] == "integer")
								{
									int newVal = stoi(j);
									cout << newVal << "\t\t\t";
									f << newVal << "\t\t\t";
								}
								else
								{
									if (column_type[nr - 1] == "float")
									{
										float newVal1 = stof(j);
										cout << newVal1 << "\t\t\t";
										f << newVal1 << "\t\t\t";
									}
									else
									{
										cout << j << "\t\t\t";
										f << j << "\t\t\t";
									}
								}
							}
							cout << endl;
							f << endl;
						}
						cout << endl << endl;
					}
					else
					{
						string c2 = comanda.substr(found + 1, comanda.length());
						map<string, string> mp = extract_condition(c2);
						map<string, string>::iterator iter = mp.begin();
						int poz, nr = 0;
						for (auto& i : (*it).column_vector)
						{
							++nr;
							if (i.name == iter->first)
								poz = nr;
							f << i.name << "\t\t\t";
							column_type.push_back(i.type);

						}
						f << endl;
						for (auto& i : (*it).inregistrari)
						{
							nr = 0;
							size_t found1 = i[poz - 1].find(iter->second);
							if (found1 != string::npos)
							{
								for (auto& j : i)
								{
									nr++;
									if (column_type[nr - 1] == "integer")
									{
										int newVal = stoi(j);
										cout << newVal << "\t\t\t";
										f << newVal << "\t\t\t";
									}
									else
									{
										if (column_type[nr - 1] == "float")
										{
											float newVal1 = stof(j);
											cout << newVal1 << "\t\t\t";
											f << newVal1 << "\t\t\t";
										}
										else
										{
											cout << j << "\t\t\t";
											f << j << "\t\t\t";
										}
									}
								}
								cout << endl;
								f << endl;
							}
						}
						cout << endl << endl;
					}
				}
			}
			if (ok == false)
				cout << "Table doesn't exist" << endl;
		}

	}
	void select(string comanda)
	{
		string table_name;
		size_t found = comanda.find(" WHERE ");
		string c1 = comanda.substr(0, found);
		map<string, int> m = extract_table_name(c1);
		map<string, int>::iterator iter = m.begin();
		bool ok = false;//presupunem ca nu exista o tabela cu acest nume
		for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
		{
			if ((*it).table_name == iter->first)
			{
				ok = true;
				isOK = true;
			}
		}
		if (ok == false)
			cout << "Table doesn't exist " << endl;
		else
		{
			table_name = iter->first;
			//extragem nume coloane
			vector<string> columns_list;
			char* poz = NULL;
			char* next_poz = NULL;
			char* cf = new char[c1.length() + 1];
			strcpy_s(cf, c1.length() + 1, c1.c_str());
			poz = strtok_s(cf, ", ", &next_poz);
			while (poz != NULL && strcmp(poz, "FROM") != 0)
			{
				if (strcmp(poz, "SELECT") != 0)
				{
					columns_list.push_back(poz);
				}
				poz = strtok_s(NULL, ", ", &next_poz);
			}

			for (auto it = tl.begin(); it != tl.end(); ++it)
			{
				if ((*it).table_name == table_name)
				{
					int nr_f = 0;
					string new_file = table_name;
					for (auto& i : file_name)
					{
						size_t found = i.find(table_name);
						if (found != string::npos)
							nr_f++;
						if (nr_f != 0)
							new_file = table_name + to_string(nr_f);
					}
					report_name = new_file;
					file_name.insert(new_file);
					ofstream f(new_file);
					vector<int> pozitii_col;
					vector<string>column_type;
					if (found != string::npos)
					{
						string c2 = comanda.substr(found + 1, comanda.length());
						map<string, string> mp = extract_condition(c2);
						map<string, string>::iterator iter = mp.begin();
						int poz_cond;
						for (auto& i : columns_list)
						{
							int nr = 0;
							for (auto& j : (*it).column_vector)
							{

								if (i == j.name)
								{
									pozitii_col.push_back(nr);
									f << j.name << "\t\t\t";
									column_type.push_back(j.type);
								}
								if (iter->first == j.name)
									poz_cond = nr;
								nr++;
							}
						}
						f << endl;
						for (auto& i : (*it).inregistrari)
						{
							if (i[poz_cond] == iter->second)
							{
								for (auto k = pozitii_col.begin(); k != pozitii_col.end(); ++k)
								{
									int poz_col = *k;
									int nr = 0;
									for (auto& j : i)
									{
										if (poz_col == nr)

										{
											f << j << "\t\t\t\t";
											cout << j << "\t\t\t\t";
										}

										nr++;

									}
								}

							}

							f << endl;
							cout << endl;
						}

					}
					else
					{
						for (auto& i : columns_list)
						{
							int nr = 0;
							for (auto& j : (*it).column_vector)
							{

								if (i == j.name)
								{
									pozitii_col.push_back(nr);
									f << j.name << "\t\t\t\t";
									column_type.push_back(j.type);
								}
								nr++;
							}
						}
						f << endl;
						for (auto& i : (*it).inregistrari)
						{
							for (auto k = pozitii_col.begin(); k != pozitii_col.end(); ++k)
							{
								int poz_col = *k;
								int nr = 0;
								for (auto& j : i)
								{
									if (poz_col == nr)

									{
										f << j << "\t\t\t\t";
										cout << j << "\t\t\t\t";
									}

									nr++;

								}
							}
							cout << endl;
							f << endl;
						}
					}
				}
			}
		}
	}
	void display_message() override
	{
		cout << "Report created";
	}
	void display_name() override
	{
		cout << report_name;
	}
};