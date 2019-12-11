#include "predicate.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


void predicate::set_name(string currentName) {

	name = currentName;
}

void predicate::set_item(string currentItem) {

	items.push_back(currentItem);
}

string predicate::to_string() {


	stringstream ss;
	ss << name << "(";
	for (unsigned i = 0; i < items.size(); i++) {

		if (i == items.size() - 1) {

			ss << items[i];
		}
		else {
			ss << items[i] << ",";
		}
	}
	ss << ")";

	return ss.str();
}

void predicate::clear() {

	name = "";
	items.clear();
}

string predicate::getName() {

	return name;
}

vector<string> predicate::getAttributes() {

	return items;
}

int predicate::getSize() {

	return items.size();
}