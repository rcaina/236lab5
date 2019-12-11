#include "Node.h"

Node::Node() {};

void Node::setNextNodes(set<int>& nodes) {
	this->nextNodes = nodes;
}

void Node::addNextNode(int nodeID) {
	this->nextNodes.insert(nodeID);
}

void Node::setVisited() {
	this->visited = true;
}

void Node::setPostOrder(int num) {
	this->postOrderNum = num;
}

string Node::toString() {
	ostringstream ss;
	vector<int> ruleNodes;
	for (int decendantNode : this->nextNodes) {
		ruleNodes.push_back(decendantNode);
	}

	for (size_t i = 0; i < ruleNodes.size(); ++i) {
		if (i != (ruleNodes.size() - 1)) {
			ss << "R" << ruleNodes.at(i) << ",";
		}
		else {
			ss << "R" << ruleNodes.at(i);
		}
	}
	return ss.str();
}

set<int> Node::getNextNodes() {
	return this->nextNodes;
}

bool Node::Visited() {
	return this->visited;
}