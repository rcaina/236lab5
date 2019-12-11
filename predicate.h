#pragma once
#ifndef PREDICATE_H
#define PREDICATE_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class predicate {

public:

	predicate() {};
	void set_name(string name);
	void set_item(string item);
	string to_string();
	void clear();
	string getName();
	vector<string> getAttributes();
	int getSize();

private:

	string name;
	vector <string> items;

};
#endif
