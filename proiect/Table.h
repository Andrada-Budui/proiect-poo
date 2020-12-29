#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Column.h"
using namespace std;

class Table
{
public:

	string table_name;
	vector<Column> column_vector;
	list<vector<string>> inregistrari;
};