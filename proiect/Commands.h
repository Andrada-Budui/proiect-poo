#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include "Column.h"
#include "Table.h"
bool isValid(string strg)
{
	const char* characters = "~`!@#$%^&*()-+=?.,<>\/[]{}'";
	char* tb_n = new char[strg.length() + 1];
	strcpy_s(tb_n, strg.length() + 1, strg.c_str());
	for (int i = 0; i < strlen(characters); i++)
		if (strchr(tb_n, characters[i]) != NULL)
			return false;
	return true;
}
bool isInteger(string nmb)
{
	char characters[] = "0123456789";
	char* number = new char[nmb.length() + 1];
	strcpy_s(number, nmb.length() + 1, nmb.c_str());
	for (int i = 0; i < strlen(number); i++)
		if (strchr(characters, number[i]) == NULL)
			return 0;
	if (number[0] == '0' && strlen(number) >= 2)
		return false;
	return true;
}

bool isFloat(string nmb)
{
	const char* characters = ".0123456789";
	char* number = new char[nmb.length() + 1];
	strcpy_s(number, nmb.length() + 1, nmb.c_str());
	for (int i = 0; i < strlen(number); i++)
		if (strchr(characters, number[i]) == NULL)
			return false;
	if (number[0] = '0' && number[1] != '.')
		return false;
	return true;
}

bool validType(string type)
{
	if (type == "integer")
		return true;
	if (type == "float")
		return true;
	if (type == "text")
		return true;
	return false;
}

class Commands
{
public:
	list<Table> tl;
	vector<string> file_name;
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
					tb.table_name = table_name;
					bool ok = false;//presupunem ca nu exista o tabela cu acest nume
					for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
						if ((*it).table_name == table_name)
						{
							ok = true;
							cout << "Table already exists";
						}

					if (ok == false)
					{   //extragere date
						ofstream g(table_name);
						file_name.push_back(table_name);
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
			cout << "Wrong table name";
		else
		{
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
				if ((*it).table_name == table_name)
				{
					ok = true;
					string table_data = table_name + "_data";
					string table_structure = table_name + "_structure";
					tl.erase(it);
					remove(table_data.c_str());
					remove(table_structure.c_str());
					cout << "Table dropped" << endl;
					break;

				}
			if (ok == false)
				cout << "Table doesn't exist" << endl;

		}
	}

	void insert(string comanda)
	{
		//Table tb;

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
				cout << "Wrong table name";
			}

			else
			{

				bool ok = false;//presupunem ca nu exista o tabela cu acest nume
				for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
				{
					if ((*it).table_name == table_name)
					{
						ok = true;
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
					cout << "Table doesn't exist";
			}
		}
		else
			cout << "missing VALUES keyword";
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
			cout << "Wrong table name or wrong file name";
		}
		else
		{

			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;

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
			cout << "Wrong table name";
		else
		{
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;
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
					file_name.push_back(new_file);
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

	void delete_f(string comanda)
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
			cout << poz << endl;
			table_name = poz;
			nr_cuv++;
			poz = strtok_s(NULL, sep, &next_poz);

		}
		if (nr_cuv > 3)
			cout << "Wrong table name";
		else
		{
			string table_data = table_name + "_data";
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;
					(*it).inregistrari.clear();
					remove(table_data.c_str());
					ofstream f(table_data, ios::binary);
					cout << "rows deleted";
				}
			}
			if (ok == false)
				cout << "Table doesn't exist";
		}
	}

	void delete_w(string comanda)
	{   //extragem nume tabela
		char* dp = new char[comanda.length() + 1];
		strcpy_s(dp, comanda.length() + 1, comanda.c_str());
		char* poz = NULL;
		char* next_poz = NULL;
		const char* sep = "W";
		poz = strtok_s(dp, sep, &next_poz);
		char* poz1 = NULL;
		next_poz = NULL;
		sep = " ";
		poz1 = strtok_s(poz, sep, &next_poz);
		string table_name;
		int nr_cuv = 0;
		while (poz1 != NULL)
		{
			/*cout << poz1 << endl;*/
			nr_cuv++;
			table_name = poz1;
			poz1 = strtok_s(NULL, sep, &next_poz);

		}

		if (nr_cuv > 3)
			cout << "Wrong table name";
		else
		{
			//extragem conditie stergere
			delete[] dp;
			dp = new char[comanda.length() + 1];
			strcpy_s(dp, comanda.length() + 1, comanda.c_str());
			string conditie, coloana, valoare;
			poz = NULL;
			next_poz = NULL;
			sep = " ";
			poz = strtok_s(dp, sep, &next_poz);
			while (poz != NULL)
			{
				conditie = poz;
				poz = strtok_s(NULL, sep, &next_poz);
			}

			poz = NULL;
			next_poz = NULL;
			sep = "=";
			char* cond = new char[conditie.length() + 1];
			strcpy_s(cond, conditie.length() + 1, conditie.c_str());
			coloana = strtok_s(cond, sep, &next_poz);
			/*cout << coloana<<endl;*/
			valoare = strtok_s(NULL, sep, &next_poz);
			/*cout << valoare;*/
			delete[] cond;

			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					string f_name = table_name + "_data";
					ok = true;
					int nr = 0, poz;
					for (auto& i : (*it).column_vector)
					{
						++nr;
						if (i.name == coloana)
							poz = nr;
					}
					int length;
					list<vector<string>> vl;
					remove(f_name.c_str());
					ofstream f(f_name, ios::binary | ios::app);
					for (auto& i : (*it).inregistrari)
					{
						if (i[poz - 1] != valoare)
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
			}
			if (ok == false)
				cout << "Table doesn't exist";

		}

	}

	void select_all(string comanda)
	{
		char* dp = new char[comanda.length() + 1];
		strcpy_s(dp, comanda.length() + 1, comanda.c_str());
		char* poz = NULL;
		char* next_poz = NULL;
		const char* sep = " ";
		string table_name;
		poz = strtok_s(dp, sep, &next_poz);
		int nr_cuv = 0;
		while (poz != NULL)
		{

			nr_cuv++;
			table_name = poz;
			poz = strtok_s(NULL, sep, &next_poz);
		}

		if (nr_cuv > 4)
			cout << "Wrong table name";
		else
		{
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;
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
					file_name.push_back(new_file);
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
			}
			if (ok == false)
				cout << "Table doesn't exist";
		}
	}

	void select_all_where(string comanda)
	{   //extragem nume tabela din conditie
		char* dp = new char[comanda.length() + 1];
		strcpy_s(dp, comanda.length() + 1, comanda.c_str());
		char* poz = NULL;
		char* next_poz = NULL;
		const char* sep = "W";
		poz = strtok_s(dp, sep, &next_poz);
		char* poz1 = NULL;
		next_poz = NULL;
		sep = " ";
		poz1 = strtok_s(poz, sep, &next_poz);
		string table_name;
		int nr_cuv = 0;
		while (poz1 != NULL)
		{
			nr_cuv++;
			table_name = poz1;
			poz1 = strtok_s(NULL, sep, &next_poz);

		}
		if (nr_cuv > 4)
			cout << "Wrong table name";
		else
		{

			//extragem conditie 
			delete[] dp;
			dp = new char[comanda.length() + 1];
			strcpy_s(dp, comanda.length() + 1, comanda.c_str());
			string conditie, coloana, valoare;
			poz = NULL;
			next_poz = NULL;
			sep = " ";
			poz = strtok_s(dp, sep, &next_poz);
			while (poz != NULL)
			{

				conditie = poz;
				poz = strtok_s(NULL, sep, &next_poz);
			}
			/*cout << conditie << endl;*/
			poz = NULL;
			next_poz = NULL;
			sep = "=";
			char* cond = new char[conditie.length() + 1];
			strcpy_s(cond, conditie.length() + 1, conditie.c_str());
			coloana = strtok_s(cond, sep, &next_poz);
			/*cout << coloana << endl;*/
			valoare = strtok_s(NULL, sep, &next_poz);
			/*	cout << valoare;*/
			delete[] cond;
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;
					int nr = 0, poz;
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
					file_name.push_back(new_file);
					ofstream f(new_file);
					vector<string>column_type;
					for (auto& i : (*it).column_vector)
					{
						++nr;
						if (i.name == coloana)
							poz = nr;
						f << i.name << "\t\t\t";
						column_type.push_back(i.type);

					}
					f << endl;
					for (auto& i : (*it).inregistrari)
					{
						nr = 0;
						if (i[poz - 1] == valoare)
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
			if (ok == false)
				cout << "Table doesn't exist";


		}
	}

	void select(string comanda)
	{
		//extragem nume tabela
		char* dp = new char[comanda.length() + 1];
		strcpy_s(dp, comanda.length() + 1, comanda.c_str());
		char* poz = NULL;
		char* next_poz = NULL;
		const char* sep = ", ";
		string table_name;
		poz = strtok_s(dp, sep, &next_poz);
		while (poz != NULL)
		{
			/*cout << poz << endl;*/
			table_name = poz;
			poz = strtok_s(NULL, sep, &next_poz);

		}

		bool ok = false;//presupunem ca nu exista o tabela cu acest nume
		for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
		{
			if ((*it).table_name == table_name)
			{
				ok = true;
			}
		}
		if (ok == false)
			cout << "Table doesn't exist " << endl << "b" << endl;

		else
		{//extragem nume colane
			vector<string> lista_coloane;
			delete[] dp;
			dp = new char[comanda.length() + 1];
			strcpy_s(dp, comanda.length() + 1, comanda.c_str());
			poz = NULL;
			next_poz = NULL;
			sep = ", ";
			poz = strtok_s(dp, sep, &next_poz);
			while (poz != NULL && strcmp(poz, "FROM") != 0)
			{
				if (strcmp(poz, "SELECT") != 0)
				{
					/*cout << poz << endl;*/
					lista_coloane.push_back(poz);
				}
				poz = strtok_s(NULL, sep, &next_poz);
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

					file_name.push_back(new_file);
					ofstream f(new_file);

					vector<string>column_type;
					vector<int> pozitii_col;
					for (auto& i : lista_coloane)
					{
						int nr = 0;
						for (auto& j : (*it).column_vector)
						{
							nr++;
							if (i == j.name) {
								pozitii_col.push_back(nr);
								f << j.name << "\t\t\t";
								column_type.push_back(j.type);
							}
						}
					}

					f << endl;
					for (auto& i : (*it).inregistrari)
					{
						int nr = 0, poz_col = 0;

						for (auto& j : i)
						{
							if (poz_col < column_type.size())
								poz_col++;
							nr++;
							bool ok = 0;
							for (auto k = pozitii_col.begin(); k != pozitii_col.end() && ok == 0; ++k)
								if (*k == nr) ok = 1;
							if (ok == 1)
							{
								if (column_type[poz_col - 1] == "integer")
								{
									int newVal = stoi(j);
									cout << newVal << "\t\t\t";
									f << newVal << "\t\t\t";
								}
								else
								{
									if (column_type[poz_col - 1] == "float")
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
						}
						cout << endl;
						f << endl;
					}
				}
			}
		}
	}

	void select_where(string comanda)
	{
		//extragem nume tabela
		 //extragem nume tabela din conditie
		char* dp = new char[comanda.length() + 1];
		strcpy_s(dp, comanda.length() + 1, comanda.c_str());
		char* poz = NULL;
		char* next_poz = NULL;
		const char* sep = "W";
		poz = strtok_s(dp, sep, &next_poz);
		char* poz1 = NULL;
		next_poz = NULL;
		sep = " ";
		poz1 = strtok_s(poz, sep, &next_poz);
		string table_name;
		int nr_cuv = 0;
		while (poz1 != NULL)
		{
			/*cout << poz1 << endl;*/
			nr_cuv++;
			table_name = poz1;
			poz1 = strtok_s(NULL, sep, &next_poz);

		}

		bool ok = false;//presupunem ca nu exista o tabela cu acest nume
		for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
		{
			if ((*it).table_name == table_name)
			{
				ok = true;
			}
		}
		if (ok == false)
			cout << "Table doesn't exist " << endl;
		else
		{   //extragem nume coloane
			vector<string> lista_coloane;
			delete[] dp;
			dp = new char[comanda.length() + 1];
			strcpy_s(dp, comanda.length() + 1, comanda.c_str());
			poz = NULL;
			next_poz = NULL;
			sep = ", ";
			poz = strtok_s(dp, sep, &next_poz);
			while (poz != NULL && strcmp(poz, "FROM") != 0)
			{
				if (strcmp(poz, "SELECT") != 0)
				{
					/*cout << poz << endl;*/
					lista_coloane.push_back(poz);
				}
				poz = strtok_s(NULL, sep, &next_poz);
			}

			//extragem conditia
			delete[] dp;
			dp = new char[comanda.length() + 1];
			strcpy_s(dp, comanda.length() + 1, comanda.c_str());
			string conditie, coloana, valoare;
			poz = NULL;
			next_poz = NULL;
			sep = " ";
			poz = strtok_s(dp, sep, &next_poz);
			while (poz != NULL)
			{

				conditie = poz;
				poz = strtok_s(NULL, sep, &next_poz);
			}
			/*cout << conditie << endl;*/
			poz = NULL;
			next_poz = NULL;
			sep = "=";
			char* cond = new char[conditie.length() + 1];
			strcpy_s(cond, conditie.length() + 1, conditie.c_str());
			coloana = strtok_s(cond, sep, &next_poz);
			/*cout << coloana << endl;*/
			valoare = strtok_s(NULL, sep, &next_poz);
			/*cout << valoare;*/
			delete[] cond;
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
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

					file_name.push_back(new_file);
					ofstream f(new_file);

					int poz_cond;
					vector<int> pozitii_col;
					vector<string>column_type;
					for (auto& i : lista_coloane)
					{
						int nr = 0;
						for (auto& j : (*it).column_vector)
						{
							nr++;
							if (i == j.name) {
								pozitii_col.push_back(nr);
								f << j.name << "\t\t\t";
								column_type.push_back(j.type);
							}
							if (coloana == j.name)
								poz_cond = nr;

						}
					}
					f << endl;
					for (auto& i : (*it).inregistrari)
					{
						if (i[poz_cond - 1] == valoare)
						{
							int nr = 0, poz_col = 0;
							for (auto& j : i)
							{
								if (poz_col < column_type.size())
									poz_col++;
								nr++;
								bool ok = 0;
								for (auto k = pozitii_col.begin(); k != pozitii_col.end(); ++k)
								{
									if (*k == nr) ok = 1;
								}
								if (ok == 1)
								{

									if (column_type[poz_col - 1] == "integer")
									{
										int newVal = stoi(j);
										cout << newVal << "\t\t\t";
										f << newVal << "\t\t\t";
									}
									else
									{
										if (column_type[poz_col - 1] == "float")
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
							}
							f << endl;
							cout << endl;
						}
					}

				}
			}
		}
	}
	void update(string comanda)
	{
		vector<string> com;
		char* dp = new char[comanda.length() + 1];
		strcpy_s(dp, comanda.length() + 1, comanda.c_str());
		char* poz = NULL;
		char* next_poz = NULL;
		const char* sep = " ";
		poz = strtok_s(dp, sep, &next_poz);
		while (poz != NULL)
		{
			com.push_back(poz);
			poz = strtok_s(NULL, sep, &next_poz);

		}
		string table_name;
		string set;
		string where;
		string setCol, setVal;
		string whereCol, whereVal;
		int nr = 0;
		for (auto& i : com)
		{
			if (i == "UPDATE")
				table_name = com[nr + 1];
			else {
				if (i == "SET") set = com[nr + 1];
				else
					if (i == "WHERE") where = com[nr + 1];
			}
			nr++;
		}
		/*cout << table_name << endl << set << endl << where;*/
		poz = NULL;
		next_poz = NULL;
		sep = "=";
		char* set_ch = new char[set.length() + 1];
		char* where_ch = new char[where.length() + 1];
		strcpy_s(set_ch, set.length() + 1, set.c_str());
		strcpy_s(where_ch, where.length() + 1, where.c_str());

		poz = strtok_s(set_ch, sep, &next_poz);
		setCol = poz;
		poz = strtok_s(NULL, sep, &next_poz);
		setVal = poz;
		/*cout << setCol << " " << setVal << endl;*/
		poz = NULL;
		poz = strtok_s(where_ch, sep, &next_poz);
		whereCol = poz;
		poz = strtok_s(NULL, sep, &next_poz);
		whereVal = poz;
		/*cout << whereCol << " " << whereVal << endl;*/
		bool ok = false;//presupunem ca nu exista tabela
		for (auto it = tl.begin(); it != tl.end(); ++it)
		{
			if ((*it).table_name == table_name)
			{
				ok = true;
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
			cout << "Table doesn't exist";

	}
};