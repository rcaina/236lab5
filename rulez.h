#pragma once
#ifndef RULEZ_H
#define RULEZ_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "predicate.h"
//#include "parser.h"

using namespace std;

class rulez {

public:
	rulez() {};

	void set_head(predicate headPred);
	void add_predicate(predicate newPred);
	void set_rulezPredicate(vector <predicate> rulezPred);
	string to_String();
	void clearCurrentRule();

	vector<predicate> getPredicates();
	predicate getHeadPred();

private:
	predicate headpredicate;
	vector <predicate> allrules;

};
#endif
