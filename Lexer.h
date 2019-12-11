#pragma once
#ifndef LEXER_H_
#define LEXER_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Tokens.h"

using namespace std;

class Lexer {

public:
	Lexer() {}
	Lexer(char* readMe);
	vector <Tokens> getVector();


private:
	vector <Tokens> myTokens;
};
#endif