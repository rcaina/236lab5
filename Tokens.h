#pragma once
#ifndef TOKENS_H_
#define TOKENS_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class Tokens {

public:
	Tokens() {}
	Tokens(string fam, string symbol, int which_line) {
		type = fam;
		sym = symbol;
		line = which_line;
	}
	string get_symbol();
	string get_type();
	int get_line();
	void set_type(string cat);
	void set_symbol(string sign);
	void set_line(int num);
	string toString();


private:
	string type;
	string sym;
	int line;


};
#endif