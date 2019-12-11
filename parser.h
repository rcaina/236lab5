#pragma once
#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Tokens.h"
#include "predicate.h"
#include "rulez.h"

using namespace std;

class parser {

public:
	parser();

	void startParser() {
		datalogProgram();
	}

	void setvector(vector <Tokens> Tokens) {

		parsingTokens = Tokens;

	}

	void toString();

	vector<predicate> getSchemes();
	vector<predicate> getFacts();
	vector<rulez> getRules();
	vector<predicate> getQueries();

private:

	vector <Tokens> parsingTokens;

	vector <predicate> schemes;
	vector <predicate> facts;
	vector <predicate> queries;
	vector <rulez> rules;
	vector <string>	stringDomain;

	predicate current;
	rulez currentrule;
	string item = "";

	int level = 0;

	void checkRemove(string);
	void datalogProgram();
	void schemeList();
	void factList();
	void ruleList();
	void queryList();
	void scheme();
	void fact();
	void rule();
	void query();
	void headPredicate();
	void newPredicate();
	void predicateList();
	void parameterList();
	void stringList();
	void idList();
	void parameter();
	void expression();
	void operate();
};

#endif
