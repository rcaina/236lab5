#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <map>
#include "Interpreter.h"

using namespace std;

Interpreter::Interpreter(parser& datalogProgram) {

	this->dL = datalogProgram;

	for (predicate scheme : dL.getSchemes()) {

		Scheme header;
		for (string list : scheme.getAttributes()) {
			header.push_back(list);
		}

		Relation r = Relation(scheme.getName(), header);
		db.insert({ r.getName(), r });
	}

	for (predicate fact : dL.getFacts()) {

		Tuple t;
		for (string attribute : fact.getAttributes()) {

			t.push_back(attribute);
		}
		db.at(fact.getName()).addTuple(t);
	}

	ruleVect = dL.getRules();
	

	graph = Graph(ruleVect);
	cout << "Dependency Graph\n";
	cout << graph.toString() << "\n";

	Graph reverseGraph = Graph();
	map<int, Node> reversedAdjList = graph.reverseAdjList();
	reverseGraph.setAdjList(reversedAdjList);

	cout << "Reversed Dependency Graph\n";
	cout << reverseGraph.toString() << "\n\n";

	vector<int> revPostOrder = reverseGraph.dfs();

	vector<set<int>> orderToEvaluate = graph.depth1Forest(revPostOrder);

	//evalAllRules(orderToEvaluate);

}

void Interpreter::evalQueries() {

	cout << "Query Evaluation\n";
	vector <string> items;
	Relation result;
	for (predicate q : dL.getQueries()) {

		cout << q.to_string() << '?';
		result = evaluatePredicate(q);

		int relationSize = result.getSize();

		if (relationSize > 0) {

			cout << " Yes(" << relationSize << ")\n";
		}
		else {

			cout << " No\n";
		}

		cout << result.toString();


	}
}

Relation Interpreter::evaluatePredicate(predicate pred) {

	vector <string> items;

	//new relation
	items = pred.getAttributes();

	map<string, int> variables;
	Scheme header;
	//loop over each param in query
	//
	Relation result = db[pred.getName()];
	vector<int> columns;

	for (unsigned i = 0; i < items.size(); i++) {

		//check if param is string or ID
		if (items.at(i).at(0) == '\'') {

			result = result.select1(i, items.at(i));
		}
		else {
			if (variables.find(items.at(i)) != variables.end()) {
				result = result.select2(variables[items.at(i)], i);
			}
			else {
				variables.insert({ items.at(i), i });
				header.push_back(items.at(i));
				columns.push_back(i);
			}
		}
		//-flowchart
	}

	result = result.project(columns);
	result = result.rename(header);

	return result;
}

// will call eval predicate function, this function is called by evaluateAllrules function
bool Interpreter::evalSingleRule(rulez rule1, set<Tuple>& tupleTracker) {

	vector <Relation> newRelations;
	vector <predicate> rulepreds = rule1.getPredicates();

	for (unsigned i = 0; i < rulepreds.size(); i++) {

		newRelations.push_back(evaluatePredicate(rulepreds[i]));
	}

	Relation rhs = newRelations[0];

	for (unsigned i = 1; i < newRelations.size(); i++) {

		rhs = rhs.joinRelation(newRelations[i]);
	}

	predicate headpred = rule1.getHeadPred();

	vector<int> keepColumns;
	vector<string> attributes = headpred.getAttributes();
	vector<string> rhsAttr = rhs.getAttributes();
	for (unsigned int i = 0; i < attributes.size(); i++) {

		for (unsigned int j = 0; j < rhsAttr.size(); j++) {

			if (attributes[i] == rhsAttr[j]) {

				keepColumns.push_back(rhs.getColumn(rhsAttr[j]));
			}
		}
	}

	rhs = rhs.project(keepColumns);

	rhs.setName(headpred.getName());
	string name = rhs.getName();

	rhs.rename(db[name].getScheme());

	int currentsize = db[name].getSize();

	db[name].unionRelation(rhs, tupleTracker);

	if (currentsize == db[name].getSize()) {

		return false;
	}

	return true;
}

void Interpreter::evalAllRules(vector<set<int>>& sccInts) {

	int count = 0;
	bool selfDependent= false;
	set<Tuple> tupleTracker;
	stringstream ss;
	int track = 0;
	int sccSize = 0;

	cout << "Rule Evaluation\n";

	for (set<int> scc : sccInts) {
		
		cout << "SCC: ";
		sccSize = scc.size();

		for (auto rule : scc) {
			
			track++;
			cout << "R" << rule;
			if (track < sccSize) {
						
				cout << ",";
			}
			else {
				cout << "\n";
			}
		}

		track = 0;

		if (scc.size() == 1) {

			for (auto& reg : graph.adjList[*scc.begin()].getNextNodes()) {

				if (*scc.begin() == reg){
					 
					selfDependent = true;
				}
			}
		}
		if (scc.size() == 1 && !selfDependent) {
			//evaluate once / call evalate single rule on ssc.begin()
			// cout
			cout << ruleVect[*scc.begin()].to_String() << ".\n";
			evalSingleRule(ruleVect[*scc.begin()], tupleTracker);

			cout <<  "1 passes: ";

			for (auto rule : scc) {

				track++;
				cout << "R" << rule;
				if (track < sccSize) {

					cout << ",";
				}
				else {
					cout << "\n";
				}
			}

			ss.clear();
		}
		else {

			while (!done) {

				done = true;
				// loop through ints intead of rules ... call singlerule at that integer
				for (int ruleID: scc) {

					cout << ruleVect[ruleID].to_String() << ".\n";
					if (evalSingleRule(ruleVect[ruleID], tupleTracker)) {

						done = false;

					}
				}
				count++;
			}

			cout << count << " passes: ";

			for (auto rule : scc) {

				track++;
				cout << "R" << rule;
				if (track < sccSize) {

					cout << ",";
				}
				else {
					cout << "\n";
				}
			}
		}
		//else fix point algorithm (change fixpoint to loop through only the set instead of all the rules)

			
		tupleTracker.clear();
		selfDependent = false;
		done = false;
		count = 0;
		track = 0;
		sccSize = 0;
	}
	cout << "\n";
}



/*ss.str("");
for (Tuple tup : tupleTracker) {

if (tup.size() > 0) {

ss << "  ";

for (unsigned i = 0; i < tup.size(); i++) {

ss << ruleVect[*scc.begin()].getHeadPred().getAttributes()[i] << "=" << tup.at(i);
if (i < tup.size() - 1) {

ss << ", ";
}
}

if (tup.size() > 0) {

ss << "\n";
}
}
}
ss.clear();*/
