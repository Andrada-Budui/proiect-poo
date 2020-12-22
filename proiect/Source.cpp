#include <iostream>
#include<string>
#include <list>
using namespace std;

class Column
{
public:
	enum  columnType { text, integer, floatingPoint };
	Column(string name, columnType type, int dimension, string defaultValue)
	{
		this->name = name;
		this->type = type;
		this->dimension = dimension;
		this->defaultValue = defaultValue;

	}
	friend istream& operator>>(istream&, Column&);
	friend ostream& operator<<(ostream&, Column);
private:
	string name;
	columnType type;
	int dimension;
	string defaultValue;

};

istream& operator>>(istream& in, Column& c)
{
	cout << "Column name (without spaces): ";
	in >> c.name;
	cout << "Column type (text/integer/floatingPoint) : ";
	string aux;
	in >> aux;
	if (aux == "text")
	{
		c.type = Column::columnType::text;
	}
	else
		if (aux == "integer")
		{
			c.type = Column::columnType::integer;
		}
		else
			if (aux == "floatingPoint")
			{
				c.type = Column::columnType::floatingPoint;
			}

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

class Tabel
{
private:
	string tableName;
	int nbOfCol;
	list<Column> columns;

public:
	//void setNbOfCol(int numar)
	//{
	//	this->nbOfCol = numar;
	//}

};