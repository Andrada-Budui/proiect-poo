#include <iostream>
#include<string>
#include <list>
#include "Verify.h"
#include "Commands.h"
#include "Column.h"
#include "Table.h"
using namespace std;

ostream& operator<<(ostream& out, Column c)
{
	out << c.name << " " << c.type << " " << c.dimension << " " << c.defaultValue << endl;
	return out;
}

int main()
{

	Verify vf;
	string comanda = "CREATE TABLE persoana ((varsta, integer, 2, 0),(nume, text, 30, no ),(adresa, text, 40, no)";
	string comanda5 = "CREATE TABLE angajati ((varsta, integer, 2, 0),(nume, text, 25, no ),(adresa, text, 40, no))";
	string comanda2 = "DROP TABLE angajati";
	string comanda3 = "INSERT INTO persoana VALUES (21,Popescu,Bucuresti)";
	string comanda4 = "INSERT INTO persoana VALUES (29,Niculescu,Cluj)";
	string comanda9 = "INSERT INTO persoana VALUES (26,Mugurel,Bucuresti)";
	string comanda6 = "DISPLAY TABLE persoana";
	string comanda7 = "DELETE FROM persoana";
	string comanda8 = "DELETE FROM persoana WHERE varsta=21";
	string comanda10 = "SELECT ALL FROM persoana";
	string comanda11 = "SELECT ALL FROM persoana WHERE nume=Mugurel";
	string comanda12 = "SELECT nume, adresa FROM persoana";
	string comanda13 = "SELECT varsta, adresa FROM persoana WHERE adresa=Cluj";
	string comanda14 = "UPDATE persoana SET nume=Minulescu WHERE adresa=Bucuresti";
	vf.check(comanda);
	vf.check(comanda3);
	vf.check(comanda4);
	vf.check(comanda9);
	/*vf.check(comanda5);*/
	//vf.check(comanda2);
	/*vf.check(comanda7);*/
	/*vf.check(comanda8);
	vf.check(comanda6);*/
	/*vf.check(comanda14);*/

	vf.check(comanda6);
	vf.check(comanda10);
	vf.check(comanda11);
	vf.check(comanda12);
	vf.check(comanda13);

	return 0;

}
