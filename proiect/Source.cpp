#include <iostream>
#include <fstream>
#include<string>
#include <list>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

class Column
{
private:
	string name;
	string type;
	int dimension;
	string defaultValue;
	list<string> valori;

public:
	Column() {}


	Column(string name, string type, int dimension, string defaultValue)
	{
		this->name = name;
		this->type = type;
		this->dimension = dimension;
		this->defaultValue = defaultValue;

	}
	friend istream& operator>>(istream&, Column&);
	friend ostream& operator<<(ostream&, Column);
	friend class Table;
	friend class Commands;
};


istream& operator>>(istream& in, Column& c)
{
	cout << "Column name (without spaces): ";
	in >> c.name;
	cout << "Column type (text/integer/floatingPoint) : ";
	in >> c.type;
	cout << "Dimension: ";
	in >> c.dimension;
	cout << "Default Value: ";
	in >> ws;
	getline(in, c.defaultValue);
	return in;
}

ostream& operator<<(ostream& out, Column c)
{
	out << c.name << " " << c.type << " " << c.dimension << " " << c.defaultValue << endl;
	return out;
}

//class Table
//{
//private:
//	string tableName;
//	int nbOfCol;
//	list<Column> columns;
//
//public:
//	//void setNbOfCol(int numar)
//	//{
//	//	this->nbOfCol = numar;
//	//}
//
//	void adaugaColoana(Column c) {
//		columns.push_back(c);
//	}
//
//	//void stergeColoana(Column c) {
//	//	// caut coloana in lista si daca exista o sterg
//	//	// parcurg si verific si cand o gasesc
//
//	//	columns.remove(c);
//	//}
//
//	const list<Column> getColoane() {
//		return columns;
//	}
//
//	/*void f() {
//		cout << "aaa";
//	}*/
//
//	Table(string name, int nbCols, list<Column> cols)
//	{
//		this->tableName = name;
//		this->nbOfCol = nbCols;
//		for (auto& i : cols)
//		{
//			columns.push_back(i);
//		}
//	}
//
//
//	map<string,list<Column>> create_table(string name, list<Column> cols)
//	{
//		map<string, list<Column>> mp;
//		mp.insert(pair<string, list<Column>>(name, cols));
//		return mp;
//	}
//};

class Commands
{
public:
	map<string, list<Column>> create_table(string name, int nbOfCol)
	{
		cout << "Nume tabela: ";
		cin >> name;
		ifstream f(name, ios::in);
		map<string, list<Column>> mp;
		list<Column> cols;
		Column c;
		while (nbOfCol > 0)
		{
			cin >> c;
			cols.push_back(c);
			nbOfCol--;

		}
		mp.insert(pair<string, list<Column >>(name, cols));
		return mp;
	}

	void insert_into(string name, map<string, list<Column>> mp)
	{
		string valoare;
		for (auto& tabele : mp)
			if (tabele.first == name)
			{
				for (auto& coloane : tabele.second)
				{
					cout << coloane.name << ": ";
					cin >> ws;
					getline(cin, valoare);
					cout << valoare;
				}
			}

		cout << endl;
	}

};

int main() {

	//list<int> lista; //  int *lista;
	//lista.push_front(10);
	//lista.push_front(12);

	//lista.remove(20);
	//// bool found = (std::find(my_list.begin(), my_list.end(), my_var) != my_list.end());
	//bool existaElement = find(lista.begin(), lista.end(), 10) != lista.end();
	//cout << existaElement;

	//for (auto i = lista.begin(); i != lista.end(); ++i) {
	//	cout << *i;
	//}

	//cout << "\nIterator explicit: ";
	//list<int>::iterator it;
	//for (it = lista.begin(); it != lista.end(); ++it) {
	//	cout << *it << " ";
	//

	/*
Tabela: Animal
Coloane: Varsta, Denumire, Culoare, Stapan

Date: 5, caine1, alb, stapan1
	6, caine2, negru, stapan2

	Tabela.Nume \n
	Tabela.Coloane. fiecare nume \n
	Tabela.Coloana1.Val1 + "   " + Tabela.Coloana2.Val1 + " " + Tabela.Coloana3.Val1....
*/

/*
Update: Pe ce tabela vreau sa fac update -> obiect Tabela -> lista de coloane
	-> cand fac update: ma uit dupa coloanele din lista tabelei

	List<Tabele> si List<Coloane>

	creez tabela: push in lista de tabele
	creez coloana: push in lista de coloane

Delete:
	-> lista_coloane.remove(...)

*/

	return 0;
}