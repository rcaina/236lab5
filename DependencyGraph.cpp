#include "DependencyGraph.h"

Graph::Graph() {};

Graph::Graph(vector<rulez>& rules) {

	for (size_t i = 0; i < rules.size(); ++i) {
		this->adjList.emplace(i, Node());
	}
	createAdjList(rules);
}

/**
* Performs Depth First Search (dfs) on graph
*
* @return vector<int> postOrderNums
*/
vector<int> Graph::dfs() {
	vector<int> postOrderNums;
	for (auto vertex : this->adjList) {
		set<int> currVisited;
		if (!vertex.second.Visited()) {
			depth1Visit(const_cast<int &>(vertex.first), currVisited, postOrderNums);
		}
	}
	return postOrderNums;
}

/**
* Recursive function to visit nodes in graph
* @param currNode
* @param currVisited
* @param postorderNums
*/
void Graph::depth1Visit(int& currNode, set<int>& currVisited, vector<int>& postorderNums) {

	currVisited.insert(currNode);
	for (auto currNeighbor : this->adjList.at(currNode).getNextNodes()) {
		if (currVisited.find(currNeighbor) == currVisited.end() && !this->adjList.at(currNeighbor).Visited()) {
			depth1Visit(currNeighbor, currVisited, postorderNums);
		}
	}
	postorderNums.push_back(currNode);
	this->adjList.at(currNode).setVisited();
}

/**
* Performs Depth First Search (dfs) on graph
* @param postOrderList
*/
vector<set<int>> Graph::depth1Forest(vector<int>& postOrderList) {

	vector<set<int>> dfsForest;
	for (int postOrderIndex = postOrderList.size() - 1; postOrderIndex >= 0; postOrderIndex--) {
		set<int> currVisited;
		int vertex = postOrderList.at(postOrderIndex);
		if (!this->adjList.at(vertex).Visited()) {
			depth1ForestVisit(vertex, currVisited);
		}
		if (!currVisited.empty()) {
			dfsForest.push_back(currVisited);
		}
	}
	//postOrderList.at(vertex)
	return dfsForest;
}

/**
* Recursive function to visit nodes in graph using dfsForest() method
* @param currNode
* @param currVisited
*/
void Graph::depth1ForestVisit(int& currNode, set<int>& currVisited) {

	currVisited.insert(currNode);
	for (auto currNeighbor : this->adjList.at(currNode).getNextNodes()) {
		if (currVisited.find(currNeighbor) == currVisited.end() && !this->adjList.at(currNeighbor).Visited()) {
			depth1ForestVisit(currNeighbor, currVisited);
		}
	}
	this->adjList.at(currNode).setVisited();
}

string Graph::toString() {
	ostringstream ss;
	for (auto node : this->adjList) {
		ss << "R" << node.first << ":" << node.second.toString() << endl;
	}
	return ss.str();
}

void Graph::createAdjList(vector<rulez>& rules) {

	for (size_t i = 0; i < rules.size(); ++i) {

		rulez currRule = rules.at(i);
		vector<predicate> RHS = currRule.getPredicates();
		for (size_t j = 0; j < RHS.size(); ++j) {
			string rhs = RHS.at(j).getName();

			for (size_t k = 0; k < rules.size(); ++k) {
				string lhs = rules.at(k).getHeadPred().getName();
				if (lhs == rhs) this->adjList.at(i).addNextNode(k); //......................
			}
		}
	}
}

map<int, Node> Graph::reverseAdjList() {

	map<int, Node> reversedAdjList;
	map<int, Node> origAdjList = this->adjList;

	for (auto currNode : origAdjList) {
		set<int> newNeighbors;
		for (auto nextNode : origAdjList) {
			for (int neighbor : nextNode.second.getNextNodes()) {
				if (currNode.first == neighbor) {
					newNeighbors.insert(nextNode.first);
				}
			}
		}
		Node newNode;
		newNode.setNextNodes(newNeighbors);
		reversedAdjList.emplace(currNode.first, newNode);
	}
	return reversedAdjList;
}

void Graph::setAdjList(map<int, Node>& adjList) {
	this->adjList = adjList;
}