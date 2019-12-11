#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctype.h>
#include "Relation.h"

using namespace std;

Relation::Relation(string name, Scheme scheme) {

	this->name = name;
	this->scheme = scheme;
}

string Relation::getName() {

	return name;
}

int Relation::getSize() {

	return tuples.size();
}

void Relation::setScheme(Scheme scheme) {

	this->scheme = scheme;
}

Scheme Relation::getScheme() {

	return scheme;
}

set<Tuple> Relation::getTuples() {

	return tuples;
}

Relation Relation::select1(int column, string val) {

	Relation result = Relation(name, scheme);

	for (Tuple t : tuples) {

		if (t.at(column).compare(val) == 0) {

			result.addTuple(t);
		}
	}

	return result;
}

Relation Relation::select2(int column1, int column2) {

	Relation result = Relation(name, scheme);

	for (Tuple t : tuples) {

		if (t.at(column1).compare(t.at(column2)) == 0) {

			result.addTuple(t);
		}
	}

	return result;
}

Scheme Relation::getAttributes() {

	return scheme;
}

Relation Relation::project(vector <int> keepColumns) {

	Relation result = Relation(name, scheme);

	Scheme header;

	for (int c : keepColumns) {

		header.push_back(scheme.at(c));
	}

	result.setScheme(header);

	for (Tuple t : tuples) {

		Tuple tup;
		for (int c : keepColumns){

			tup.push_back(t.at(c));
		}

		result.addTuple(tup);
	}

	return result;
}

Relation Relation::rename(Scheme header) {

	Relation result = *this;

	result.setScheme(header);

	return result;
}

void Relation::addTuple(Tuple tup) {

	tuples.insert(tup);
}

string Relation::setName(string newName) {

	name = newName;

	return name;
}

string Relation::toString() {

	stringstream ss;

	ss.str("");
	for (Tuple tup : tuples) {

		if (tup.size() > 0) {

			ss << "  ";

			for (unsigned i = 0; i < tup.size(); i++) {

				ss << scheme[i] << "=" << tup.at(i);
				if (i < tup.size() - 1) {

					ss << ", ";
				}
			}

			if (tup.size() > 0) {

				ss << "\n";
			}
		}
	}

	return ss.str();
}

int Relation::getColumn(string attribute) {

	for (unsigned i = 0; i < scheme.size(); i++) {

		if (scheme.at(i).compare(attribute) == 0) {

			return i;
		}
	}

	return -1;
}

bool Relation::isJoinable(const Tuple& tuple1, const Tuple& tuple2, map<int, int> matchingCol) {

	for (const auto& pair : matchingCol) {

		int column1 = pair.first;
		int column2 = pair.second;

		if (tuple1[column1] != tuple2[column2]) {

			return false;
		}
	}
	return true;
}

Scheme Relation::combineScheme(const Scheme& scheme1, const Scheme& scheme2) const {

	Scheme newHeader;
	unordered_set <string> schemeCopy;

	for (const string& name : scheme1) {

		newHeader.push_back(name);
		schemeCopy.insert(name);
	}
	for (const string& name : scheme2) {
		if (schemeCopy.find(name) == schemeCopy.end()) {
			newHeader.push_back(name);
		}
	}

	return newHeader;
}

Tuple Relation::combineTuples(const Tuple& tuple1, const Tuple& tuple2, const Scheme& scheme1, const Scheme& scheme2) {

	Tuple newTuple;
	unordered_set <string> schemeCopy;
	

	for (unsigned int i = 0; i < tuple1.size(); i++) {

		newTuple.push_back(tuple1[i]);
		schemeCopy.insert(scheme1[i]);
	}
	for (unsigned int i = 0; i < tuple2.size(); i++) {

		if (schemeCopy.find(scheme2[i]) == schemeCopy.end()) {
			newTuple.push_back(tuple2[i]);
		}
	}

	return newTuple;
}

map<int, int> Relation::getColumnstoMatch(const Scheme& scheme1, const Scheme& scheme2) const {

	map<string, int> regularScheme;
	map<int, int> columnstoMatch;

	for (unsigned int i = 0; i < scheme1.size(); i++) {

		regularScheme[scheme1[i]] = i;
	}

	for (unsigned int i = 0; i < scheme2.size(); i++) {

		if (regularScheme.find(scheme2[i]) != regularScheme.end()) {

			int index = regularScheme[scheme2[i]];

			columnstoMatch[index] = i;
		}
	}

	return columnstoMatch;
}

Relation Relation::joinRelation(Relation& rhs) {

	Scheme newScheme = combineScheme(this->scheme, rhs.scheme);

	Relation result(this->name, newScheme);

	map<int, int> columnstoMatch = getColumnstoMatch(this->scheme, rhs.scheme);

	for (Tuple tups : this->getTuples()) {

		for (Tuple rhstups : rhs.getTuples()) {

			if (isJoinable(tups, rhstups, columnstoMatch)) {

				Tuple newTup = combineTuples(tups, rhstups, this->scheme, rhs.scheme);
				result.addTuple(newTup);

			}
		}
	}

	return result;
}

void Relation::unionRelation(Relation& rhs, set<Tuple>& tupleTracker) {
	
	Relation updatedRelation(this->name, this->scheme);

	set<Tuple> combinedtuples = this->tuples;

	for (Tuple tup : rhs.getTuples()) {

		if (combinedtuples.insert(tup).second) {

			updatedRelation.addTuple(tup);
			tupleTracker.insert(tup);

		}
	}

	this->tuples = combinedtuples;
	
	cout << updatedRelation.toString();
}

