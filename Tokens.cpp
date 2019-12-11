#include "Tokens.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

string Tokens::get_type() {

	return type;
}

string Tokens::get_symbol() {

	return sym;
}

int Tokens::get_line() {

	return line;
}

void Tokens::set_type(string cat) {

	type = cat;
}

void Tokens::set_symbol(string sign) {

	sym = sign;
}

void Tokens::set_line(int num) {

	line = num;
}
string Tokens::toString() {

	stringstream ss;
	ss << "(" << type << ",\"" << sym << "\"," << line << ")" << "\n";
	return ss.str();
}