#pragma once
#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <vector>
#include <map>
#include <stack>
#include <deque>
#include <iostream>

#include "rulez.h"
#include "Node.h"

using namespace std;

class Graph {

public:

	Graph();
	Graph(vector<rulez>& rules);

	void setAdjList(map<int, Node>& adjList);
	//void depth1Tree();
	vector<set<int>> depth1Forest(vector<int>& postOrderList);
	vector<int> dfs();
	string toString();
	map <int, Node> adjList;

	map<int, Node> reverseAdjList();

private:

	//map <int, Node> adjList;
	void createAdjList(vector<rulez>& rules);
	void depth1Visit(int& currentNode, set<int>& visited, vector<int>& postOrderList);
	void depth1ForestVisit(int &currentNode, set<int>& currentVisited);
	
	
};

#endif
