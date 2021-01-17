#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include "Column.h"
#include "Table.h"
#include <map>
#include <set>

map<string, int> extract_table_name(string c1)
{
	map<string, int> m;
	char* cf1 = new char[c1.length() + 1];
	strcpy_s(cf1, c1.length() + 1, c1.c_str());
	char* poz = NULL;
	char* next_poz = NULL;
	poz = strtok_s(cf1, " ", &next_poz);
	int nr_cuv = 0;
	while (poz != NULL)
	{
		nr_cuv++;
		c1 = poz;
		poz = strtok_s(NULL, " ", &next_poz);
	}
	m.insert(pair<string, int>(c1, nr_cuv));
	return m;

}

map<string, string> extract_condition(string c2)
{
	map<string, string> m;
	char* poz = NULL;
	char* next_poz = NULL;
	char* cf2 = new char[c2.length() + 1];
	strcpy_s(cf2, c2.length() + 1, c2.c_str());
	string column_name = strtok_s(cf2 + 6, "=", &next_poz);
	string value = strtok_s(NULL, "=", &next_poz);
	m.insert(pair<string, string>(column_name, value));
	return m;
}

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

list<Table> tl;
set<string> file_name;

class Commands
{
public:

	virtual void display_message() = 0;
	virtual void display_name() = 0;

};
