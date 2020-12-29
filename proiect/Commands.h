#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Column.h"
#include "Table.h"

class Commands
{
public:
	list<Table> tl;
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
			/*cout << table_name;*/

			bool ok = false;//presupunem ca nu exista o tabela cu acest nume
			for (auto it = tl.begin(); it != tl.end() && ok == false; ++it)
			{
				if ((*it).table_name == table_name)
				{
					ok = true;
					cout << endl;
					for (auto& i : (*it).inregistrari)
					{
						for (auto& j : i)
							cout << j << "\t\t";
						cout << endl;
					}
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
};