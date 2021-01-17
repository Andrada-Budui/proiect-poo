#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Column
{
public:
	string name;
	string type;
	string dimension;
	string defaultValue;

	Column() {}

	Column(string name, string type, string dimension, string defaultValue)
	{
		this->name = name;
		this->type = type;
		this->dimension = dimension;
		this->defaultValue = defaultValue;

	}
	friend ostream& operator<<(ostream&, Column);
};