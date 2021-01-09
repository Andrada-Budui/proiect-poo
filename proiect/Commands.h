#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include "Column.h"
#include "Table.h"

class Commands
{
public:
	list<Table> tl;
	vector<string> file_name;
	void create_table(string comanda)
	{
		Table tb;
		vector<string> v;
		//extragere nume tabela
		/*cout << endl;*/
		char* sc = new char[comanda.length() + 1];
		strcpy_s(sc, comanda.length() + 1, comanda.c_str());

		char* poz = NULL;
		char* next_poz = NULL;
		const char* chr = "(";
		poz = strtok_s(sc, chr, &next_poz);
		/*cout << poz << endl;*/

		char* poz1 = NULL;
		next_poz = NULL;
		chr = " ";
		string nume_tabela;
		int nr_cuv = 0;
		poz1 = strtok_s(poz, chr, &next_poz);
		while (poz1 != NULL)
		{
			/*cout << poz1<<endl;*/
			nume_tabela = poz1;
			++nr_cuv;
			poz1 = strtok_s(NULL, chr, &next_poz);
		}

		if (nr_cuv > 3)
			cout << "wrong table name" << endl;
		else {
			/*cout << nume_tabela;*/
			tb.table_name = nume_tabela;
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
				if ((*it).table_name == nume_tabela)
				{
					ok = true;
					cout << "Table already exists";
				}

			if (ok == false)
			{//extragere date
				/*cout << endl;*/
				size_t found = comanda.find("(");
				string atribute = comanda.substr(found);
				char* s = new char[atribute.length() + 1];
				strcpy_s(s, atribute.length() + 1, atribute.c_str());
				/*cout << s;*/
				/*cout << endl;*/
				chr = "( ,)";
				poz = NULL;
				next_poz = NULL;
				poz = strtok_s(s, chr, &next_poz);
				while (poz != NULL)
				{
					/*cout << poz<<endl;*/
					v.push_back(poz);
					poz = strtok_s(NULL, chr, &next_poz);
				}
				vector<Column> vc;
				vector<string>::iterator i = v.begin();
				while (i != v.end())
				{
					Column c;
					c.name = *i;
					++i;
					c.type = *i;
					++i;
					c.dimension = *i;
					++i;
					c.defaultValue = *i;
					++i;
					/*cout << c;*/
					vc.push_back(c);
				}
				tb.column_vector = vc;
				/*	for (auto& i : tb.column_vector)
						cout << i << endl;*/
				tl.push_back(tb);
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
			/*cout << poz<<endl;*/
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
					tl.erase(it);
					cout << "Table dropped";
					break;

				}
			if (ok == false)
				cout << "Table doesn't exist";

		}
	}

	void insert(string comanda)
	{
		//Table tb;
		vector<string> linie;
		char* dp = new char[comanda.length() + 1];
		strcpy_s(dp, comanda.length() + 1, comanda.c_str());
		char* poz = NULL;
		char* next_poz = NULL;
		const char* sep = "V";
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
			/*cout << table_name;*/
			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;
					size_t found = comanda.find("(");
					string atribute = comanda.substr(found);
					char* s = new char[atribute.length() + 1];
					strcpy_s(s, atribute.length() + 1, atribute.c_str());
					/*cout << s;*/
					/*cout << endl;*/
					sep = "(,)";
					poz = NULL;
					next_poz = NULL;
					poz = strtok_s(s, sep, &next_poz);
					while (poz != NULL)
					{
						/*cout << poz<<endl;*/
						linie.push_back(poz);
						poz = strtok_s(NULL, sep, &next_poz);
					}
					/*for (auto& i : linie)
						cout << i << "\t\t ";*/
					(*it).inregistrari.push_back(linie);

				}
			}
			if (ok == false)
				cout << "Table doesn't exist";
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
			/*cout << poz << endl;*/
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
			cout << table_name;

			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;
					(*it).inregistrari.clear();
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
			/*cout << table_name;*/
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
				/*cout << poz << endl;*/
				conditie = poz;
				poz = strtok_s(NULL, sep, &next_poz);
			}
			cout << conditie << endl;
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
					ok = true;
					int nr = 0, poz;
					for (auto& i : (*it).column_vector)
					{
						++nr;
						if (i.name == coloana)
							poz = nr;
					}
					list<vector<string>> vl;

					for (auto& i : (*it).inregistrari)
					{
						if (i[poz - 1] != valoare)
							vl.push_back(i);
					}

					(*it).inregistrari.clear();
					(*it).inregistrari = vl;

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
					/*bool ok1 = false;*/
					for (auto& i : (*it).inregistrari)
					{
						if (i[poz_cond - 1] == valoare)
						{
							/*ok1 = true;*/
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

					/*if (ok1 == false)
						cout << "No Data Found";*/

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
		cout << setCol << " " << setVal << endl;
		poz = NULL;
		poz = strtok_s(where_ch, sep, &next_poz);
		whereCol = poz;
		poz = strtok_s(NULL, sep, &next_poz);
		whereVal = poz;
		cout << whereCol << " " << whereVal << endl;
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

			}
		}
		if (!ok)
			cout << "Table doesn't exist";

	}
};