//#include "parser.h"
#include "rulez.h"
#include "predicate.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void rulez::set_head(predicate headPred) {

	headpredicate = headPred;

}

void rulez::add_predicate(predicate newPred) {

	allrules.push_back(newPred);

}

string rulez::to_String() {

	stringstream ss;
	ss << headpredicate.to_string() << " :- ";
	for (unsigned i = 0; i < allrules.size(); i++) {

		if (i == allrules.size() - 1) {

			ss << allrules[i].to_string();
		}
		else {
			ss << allrules[i].to_string() << ",";
		}
	}

	return ss.str();
}
void rulez::clearCurrentRule() {

	allrules.clear();
	headpredicate.clear();
}

vector<predicate> rulez::getPredicates() {

	return allrules;
}

predicate rulez::getHeadPred() {

	return headpredicate;
}