#pragma once

#include "Pathfinder2D.hpp"
#include <cmath>
#include <queue>
#include <iostream>



void Pathfinder2D::vec2DNormalize(sf::Vector2f& vec) {
	sf::Vector2f temp = sf::Vector2f(vec.x - currentPosition.x, vec.y - currentPosition.y);
	float z = sqrt((temp.x * temp.x) + (temp.y * temp.y));


	moveDirection.x = temp.x / z;
	moveDirection.y = temp.y / z;


}


Pathfinder2D::Pathfinder2D(sf::Vector2f& position) : currentPosition(position)
{
	//graph = graph_;
	stillMoving = 0;
	stillSearching = 0;
	speed = 0.5;
	moveDirection.x = 0;
	moveDirection.y = 0;
	//currPos = currPos_;
}

Pathfinder2D::~Pathfinder2D()
{
}



void Pathfinder2D::Update()
{

	if (VecPath.empty()) {
		return;
	}

	//std::cout << Distance(currentPosition, VecPath.back()) << "\n";
	if (Distance(currentPosition,VecPath.back()) < (float)1.0)
	{
		currentPosition = VecPath.back();
		VecPath.pop_back();
		//vec2DNormalize(VecPath.back());

	}
	else
	{
		 vec2DNormalize(VecPath.back());
		 currentPosition += (moveDirection * (float)0.5);
		//playerSprite.setPosition();
	}
}


void Pathfinder2D::Move(sf::Vector2f target) {
	//pathfind for target;
	//if free just move
	
	if (AStar(currentPosition, target)) {
		//Update();
	}
	else {
		
	}
	/*VecPath.push_back(target);
	vec2DNormalize(target);
	*/
	//if not free
	//movealongPath();
}
	


void Pathfinder2D::stop() {
	path.clear();
}

void Pathfinder2D::setPath(std::vector<sf::Vector2f> path_) {
	VecPath = path_;
}


class Compare {
public:

	bool operator() (std::pair<int, float> a, std::pair<int, float> b) {
		return a.second > b.second;
	}

};


bool Pathfinder2D::AStar(sf::Vector2f source, sf::Vector2f target) {

	std::priority_queue<std::pair<int, float>,
						std::vector< std::pair<int, float> >,
						Compare> pq;

	int sourceIndex = graph.PosToIndex(source.x, source.y);
	int targetIndex = graph.PosToIndex(target.x, target.y);

	if (sourceIndex == targetIndex)
		return true;

	int numNodes = graph.nodesList.size();
	std::vector<int> realCost(numNodes, -1);
	std::vector<int> heuristicCost(numNodes, -1);
	//std::vector<int> cameFrom(numNodes, -1);
	std::vector<bool> isValid(numNodes, true);

	//graph.path.reserve(numNodes);
	if (path.size() == 0)
		path.insert(path.begin(), numNodes, -1);


	float hCost;
	float rCost;

	pq.push(std::make_pair(sourceIndex, 0));
	std::pair<int, float> nextNode;

	while (!pq.empty()) {
		nextNode = pq.top();
		pq.pop();

		if (!(isValid[nextNode.first]))
			continue;

		if (nextNode.first == targetIndex) {
			VecPath.push_back(graph.nodesList[path[targetIndex]].pos);
			for (auto elem = path[targetIndex]; elem != sourceIndex; elem = path[elem]) {
				VecPath.push_back(graph.nodesList[path[elem]].pos);
			}
			return true;
		}

		isValid[nextNode.first] = false;
		for (const auto& edge : graph.edgeList[nextNode.first]) {

			hCost = Distance(target, graph.nodesList[edge.to].pos);
			rCost = realCost[nextNode.first] + edge.cost;

			if (realCost[edge.to] == -1) {
				heuristicCost[edge.to] = rCost + hCost;
				realCost[edge.to] = rCost;

				pq.push(std::make_pair(edge.to, rCost + hCost));

				path[edge.to] = nextNode.first;

			}
			else if (realCost[edge.to] > rCost) {
				heuristicCost[edge.to] = rCost + hCost;
				realCost[edge.to] = rCost;

				path[edge.to] = nextNode.first;

				pq.push(std::make_pair(edge.to, rCost + hCost));
			}

		}

	}
	return false;


}
