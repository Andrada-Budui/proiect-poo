#include <iostream>
#include<string>
#include <list>
#include "Verify.h"
#include "Commands.h"
#include "Column.h"
#include "Table.h"
#include "Options.h"
#include "Option1.h"
#include "Option2.h"
#include "Option3.h"
#include "Option4.h"


using namespace std;

ostream& operator<<(ostream& out, Column c)
{
	out << c.name << " " << c.type << " " << c.dimension << " " << c.defaultValue << endl;
	return out;
}

int main(int argc, char* argv[])
{
	Verify vf;
	string command;
	for (int i = 1; i < argc; i++)
	{
		string file_name = argv[i];
		vf.file(file_name);
	}
	Option1 op1;
	Option2 op2;
	Option3 op3;
	Option4 op4;

	Options** op = new Options * [4];
	op[0] = &op1;
	op[1] = &op2;
	op[2] = &op3;
	op[3] = &op4;

	int choice;
	cout << "MENU OPTION" << endl;
	cout << "1  -  GENERAL REPORT" << endl;
	cout << "2  -  CUSTOMIZED REPORT" << endl;
	cout << "3  -  ALTER TABLE" << endl;
	cout << "4  -  USE EXISTING FILE COMMANDS";
	cout << endl << endl;
	string ok = "yes";
	while (ok == "yes")
	{
		cout << "Press 1 or 2 or 3 or 4: ";
		cin >> choice;
		if (choice == 1)
		{
			op[0]->option();
			cout << endl << "Please, type in your command : ";
			cin >> ws;
			getline(cin, command);
			vf.check(command);
		}
		if (choice == 2)
		{
			op[1]->option();
			cout << endl << "Please, type in your command : ";
			cin >> ws;
			getline(cin, command);
			vf.check(command);
		}
		if (choice == 3)
		{
			op[2]->option();
			cout << endl << "Please, type in your command : ";
			cin >> ws;
			getline(cin, command);
			vf.check(command);
		}
		if (choice == 4)
		{
			string file_name;
			op[3]->option();
			cin >> file_name;
			vf.file(file_name);
		}
		cout << "Continue? yes/no : ";
		cin >> ok;
	}
	return 0;

}
