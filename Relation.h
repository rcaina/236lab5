#pragma once
#ifndef RELATION_H
#define RELATION_H

#include <set>
#include <map>
#include <unordered_set>
#include "Tuple.h"
#include "Scheme.h"

using namespace std;

class Relation {

public:
	Relation() {}
	Relation(string name, Scheme scheme);
	Relation select1(int column, string val);
	Relation select2(int column1, int column2);
	Relation project(vector <int> keepColumns);
	Relation rename(Scheme header);
	/*Relation rename(Relation& compareRelation);*/
	bool isJoinable(const Tuple& tuple1, const Tuple& tuple2, map<int, int> matchingCol);
	Scheme combineScheme(const Scheme& scheme1, const Scheme& scheme2) const;
	Tuple combineTuples(const Tuple& tuple1, const Tuple& tuple2, const Scheme& scheme1, const Scheme& scheme2);
	map<int, int> getColumnstoMatch(const Scheme& scheme1, const Scheme& scheme2) const;

	Relation joinRelation(Relation& rhs);
	void unionRelation(Relation& rhs, set<Tuple>& tupleTracker);

	string setName(string newname);
	string getName();
	void setScheme(Scheme scheme);
	Scheme getScheme();
	set<Tuple> getTuples();

	string toString();
	void addTuple(Tuple tup);
	int getSize();
	int getColumn(string attribute);

	Scheme getAttributes();

private:
	string name;
	Scheme scheme;
	set <Tuple> tuples;

};
#endif

