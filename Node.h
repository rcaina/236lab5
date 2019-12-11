#pragma once
#ifndef NODE_H
#define NODE_H

#include <set>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Node {

public:
	Node();

	void setNextNodes(set<int>& nodes);
	void addNextNode(int nodeID);
	void setVisited();
	bool Visited();
	void setPostOrder(int num);

	set<int> getNextNodes();
	string toString();

private:
	set<int> nextNodes;
	bool visited = false;
	int postOrderNum = -1;
};

#endif