/*
 * Node.cpp
 *
 *  Created on: Mar 26, 2018
 *      Author: crae
 */

#include "Node.h"

#include <algorithm>
#include <cmath>

Node::Node(double x, double y) :
	_x(x),
	_y(y),
	_parent()
{

}

Node::~Node()
{
	for(auto connection : _connections){
		connection->removeConnection(this);
	}
}

bool Node::addConnection(Node* connection)
{
	for(auto existingConnection : this->_connections){
		if(connection == existingConnection){
			return false;
		}
	}

	this->_connections.push_back(connection);
	connection->_connections.push_back(this);
	return true;
}

bool Node::removeConnection(Node* connection)
{
	auto thisConnection =  std::find(this->_connections.begin(), this->_connections.end(), connection);

	if(thisConnection != this->_connections.end()){
		this->_connections.erase(thisConnection);
		auto thatConnection = std::find(connection->_connections.begin(), connection->_connections.end(), this);
		connection->_connections.erase(thatConnection);
		return true;
	}

	return false;
}

double Node::computeCost(const Node* connection, const Node* target)
{
	double connectionDistance = sqrt(pow(connection->_x - this->_x, 2) + pow(connection->_y - this->_y, 2));
	double targetDistance = sqrt(pow(target->_x - connection->_x, 2) + pow(target->_y - connection->_y, 2));

	return connectionDistance + targetDistance;
}

void Node::setParent(Node* parent)
{
	_parent = parent;
}

void Node::removeParent()
{
	_parent = NULL;
}

Node* Node::getParent()
{
	return _parent;
}

std::vector<Node*> Node::getConnections(){
	return _connections;
}
