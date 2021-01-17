#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Commands.h"
#include "CREATE_TABLE.h"
#include "DROP_TABLE.h"
#include "INSERT.h"
#include "DELETE.h"
#include "REPORT.h"
#include "UPDATE.h"
using namespace std;

class Verify {

public:
	CREATE_TABLE ct;
	DROP_TABLE dt;
	INSERT ins;
	UPDATE upd;
	DELETE del;
	REPORT rep;

	void file(string file_name)
	{
		ifstream f(file_name);
		if (f.is_open())
		{
			string comanda;
			while (getline(f, comanda))
			{
				check(comanda);

			}
		}
	}

	void check(string comanda)
	{

		size_t found = comanda.find("CREATE TABLE ");
		if (found != string::npos)
		{
			ct.create_table(comanda);
			if (ct.isOK)
			{

				ct.display_message();
				cout << " ";
				ct.display_name();
				cout << endl;
			}

		}
		/*else cout << "wrong command form";*/

		found = comanda.find("DROP TABLE ");
		if (found != string::npos)
		{
			dt.drop_table(comanda);
			if (dt.isOK)
			{
				dt.display_message();
				cout << " ";
				dt.display_name();
				cout << endl;
			}
		}

		found = comanda.find("INSERT INTO ");
		size_t found1 = comanda.find(" VALUES ");
		if (found != string::npos && found1 != string::npos)
		{
			ins.insert(comanda);
			if (ins.isOK)
			{
				ins.display_message();
				cout << " into table ";
				ins.display_name();
				cout << endl;
			}
		}

		found = comanda.find("DISPLAY TABLE");
		if (found != string::npos)
		{
			rep.display_table(comanda);
			if (rep.isOK)
			{
				rep.display_message();
				cout << " ";
				rep.display_name();
				cout << endl;
			}
		}

		found = comanda.find("DELETE FROM ");
		if (found != string::npos)
		{
			del.delete_from(comanda);
			if (del.isOK)
			{
				del.display_message();
				cout << " ";
				del.display_name();
				cout << endl;
			}
		}

		found = comanda.find("SELECT ALL FROM ");
		found1 = comanda.find("SELECT ");
		if (found != string::npos)
		{
			rep.select_all(comanda);
			if (rep.isOK)
			{
				rep.display_message();
				cout << " ";
				rep.display_name();
				cout << endl;
			}
		}
		else
			if (found1 != string::npos)
			{
				rep.select(comanda);
				if (rep.isOK)
				{
					rep.display_message();
					cout << " ";
					rep.display_name();
					cout << endl;
				}
			}

		found = comanda.find("UPDATE ");
		found1 = comanda.find(" SET ");
		size_t found2 = comanda.find(" WHERE ");
		if (found != string::npos && found1 != string::npos && found2 != string::npos)
		{
			upd.update(comanda);
			if (upd.isOK)
			{
				upd.display_message();
				cout << " ";
				upd.display_name();
				cout << endl;
			}
		}

		found = comanda.find("IMPORT ");
		found1 = comanda.find(".csv");
		if (found != string::npos && found1 != string::npos)
		{
			ins.insert_csv(comanda);
			if (ins.isOK)
			{
				ins.display_message();
				cout << " into table ";
				ins.display_name();
				cout << endl;
			}
		}
	}
};