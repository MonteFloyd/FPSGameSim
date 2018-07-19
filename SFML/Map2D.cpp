#include "Map2D.hpp"
#include <queue>






bool Map2D::getClosestWallIntersect(sf::Vector2f A, sf::Vector2f B, float& distance, sf::Vector2f & intersection)
{
	distance = 99999;
	float dist = 0;
	bool found = false;
	auto curWall = walls.begin();
	sf::Vector2f point;
	for (curWall; curWall != walls.end(); ++curWall)
	{		

		if (getIntersectionRaycast(A, B, (curWall)->A, (curWall)->B, dist, point))
		{
			if (dist < distance)
			{
				found = true;
				distance = dist;
				intersection = point;
			}
		}

		if (getIntersectionRaycast(A, B, (curWall)->B, (curWall)->C, dist, point))
		{
			if (dist < distance)
			{
				found = true;
				distance = dist;
				intersection = point;
			}
		}

		if (getIntersectionRaycast(A, B, (curWall)->C, (curWall)->D, dist, point))
		{
			if (dist < distance)
			{
				found = true;
				distance = dist;
				intersection = point;
			}
		}

		if (getIntersectionRaycast(A, B, (curWall)->D, (curWall)->A, dist, point))
		{
			if (dist < distance)
			{
				found = true;
				distance = dist;
				intersection = point;
			}
		}

	}

	return found;
}





bool checkEdgeWallIntersect(Edge e, Wall w) {

	if (lineIntersect2D(e.fromPos, e.toPos, w.A, w.B)) {
		return true;
	}
	else if (lineIntersect2D(e.fromPos, e.toPos, w.B, w.C)) {
		return true;
	}
	else if (lineIntersect2D(e.fromPos, e.toPos, w.C, w.D)) {
		return true;
	}
	else if (lineIntersect2D(e.fromPos, e.toPos, w.D, w.A)) {
		return true;
	}

	return false;

}


void Map2D::clearEdges() {
	int it;
	for (auto& list : navGraph.edgeList) {
		for (it = (list.size()-1); it >= 0; --it ) {
			for (auto& wall : walls) {
				if (checkEdgeWallIntersect(list[it], wall)) {
					std::swap(list[it], list[list.size()-1]);
					list.pop_back();
					break;

				}
				//list.remove_if((checkEdgeWallIntersect(*it, wall)));
				
			
			}	
		}
	}
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::VertexArray quad(sf::Quads, 4);

	quad[0] = A;
	quad[1] = B;
	quad[2] = C;
	quad[3] = D;

	target.draw(quad, states);


}

float TwoDistance(sf::Vector2f a, sf::Vector2f b) {
	return std::sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

void Map2D::addWall(sf::Vector2f a, sf::Vector2f b,sf::Vector2f c, sf::Vector2f d) {
	Wall w(a, b, c, d);
	walls.push_back(w);
}

void Map2D::addNode(const sf::Vector2f & node)
{
	nodes.push_back(node);
}

int NavigationGraph::PosToIndex(float x, float y){ 
	int col = (x - (tileWidth / 2)) / tileWidth;
	int row = (y - (tileHeight / 2)) / tileHeight;

	if (col < 0) { col = 0; }
	if (row < 0) { row = 0; }

	return row * numofTilesX + col;
	/*int index = (int)(numofTilesX * x / tileWidth) + ((int)((numofTilesY)* y / tileHeight) * numofTilesX);
	if (index > nodesList.size()) {
		return (int)(nodesList.size() - 1);
	}

	return index;*/
}
/*void Map2D::addNode(const sf::Vector2f & node)
{
	sf::CircleShape circle(3);
	circle.setPosition(node);

	nodes.push_back(circle);
}*/

/*const sf::Drawable& Map2D::popDrawable()
{
	const auto& drawable = walls.back();
	walls.pop_back();
	return drawable;
}*/


void Map2D::buildGraph(int mapWidth, int mapHeight, int NumTileX, int NumTileY)
{
	
	double TileWidth = (double)mapWidth / (double)NumTileX;
	double TileHeight = (double)mapHeight / (double)NumTileY;

	double midX = TileWidth / 2;
	double midY = TileHeight / 2;

	navGraph.setWidth(mapWidth);
	navGraph.setHeight(mapHeight);
	navGraph.tileHeight = TileHeight;
	navGraph.tileWidth = TileWidth;
	navGraph.setMaxY(NumTileY);
	navGraph.setMaxX(NumTileX);
	navGraph.edgeList = std::vector< std::vector<Edge> >(NumTileX*NumTileY);
	//navGraph.edgeList.reserve(NumTileX*NumTileY);



	for (int row = 0; row < NumTileY; ++row) {
		for (int col = 0; col < NumTileX; ++col) {
			//addNode(sf::Vector2f( (float)(midX + (col*TileWidth)), (float)(midY + (row*TileHeight))));
			navGraph.addNode(Node(sf::Vector2f((float)(midX + (col*TileWidth)), (float)(midY + (row*TileHeight))),(int)navGraph.nodesList.size()));

		}


	}


	for (int row = 0; row < NumTileY; ++row) {
		for (int col = 0; col < NumTileX; ++col) {
			navGraph.addEdges(row, col);
			

		}

	}



	


}



void Map2D::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	/*for (const auto& drawable : walls) {
		target.draw(drawable, states);
	}*/

	for (const auto& wall : walls) {
		wall.draw(target,states);
	}

	/*for (const auto& node : nodes) {
		target.draw(, states);
	}*/
}



void NavigationGraph::addEdges(int row,int col) {
	int nodeRow;
	int nodeCol;
	sf::Vector2f thisNode;
	sf::Vector2f neighborNode;
	float distance;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			nodeCol = col + j;
			nodeRow = row + i;


			if (i == 0 && j == 0) {

			}
			else if ((nodeRow < numofTilesY) && (nodeRow >= 0) && (nodeCol < numofTilesX) && (nodeCol >= 0)) {
				thisNode = nodesList.at(row*numofTilesX + col).pos;
				neighborNode = nodesList.at(nodeRow*numofTilesX + nodeCol).pos;

				distance = Distance(thisNode, neighborNode);

				edgeList[row*numofTilesX + col].push_back(Edge(row*numofTilesX + col,
																nodeRow*numofTilesX + nodeCol,
					thisNode,
					neighborNode,
																distance));

			}

		}

	}
}


void Map2D::removeInvalidEdges() {
	for (const auto& list : navGraph.edgeList) {
		for (const auto& edge : list) {
			sf::Vertex line[] =
			{
				sf::Vertex(edge.fromPos),
				sf::Vertex(edge.toPos)
			};

		}
	}


}



class Compare {
public:

	bool operator() (std::pair<int, float> a,std::pair<int,float> b) {
		return a.second > b.second;
	}

};









/////// OLD STUFF

/*void Map2D::buildGraph(int mapWidth, int mapHeight, int maxtileX, int maxtileY)
{

double TileWidth = (double)mapWidth / (double)maxtileX;
double TileHeight = (double)mapHeight / (double)maxtileY;

double midX = TileWidth / 2;
double midY = TileHeight / 2;

navGraph.setWidth(mapWidth);
navGraph.setHeight(mapHeight);
navGraph.setMaxY(maxtileY);
navGraph.setMaxX(maxtileX);
navGraph.edgeList = std::vector< std::list<Edge> >(maxtileX*maxtileY);
//navGraph.nodeVec<std::vector<Node> >(maxtileX);
//navGraph.edgeList.reserve(NumTileX*NumTileY);



for (int row = 0; row < maxtileX; ++row) {
navGraph.nodeVec.push_back(std::vector<Node>());
for (int col = 0; col < maxtileY; ++col) {
//addNode(sf::Vector2f( (float)(midX + (col*TileWidth)), (float)(midY + (row*TileHeight))));
navGraph.nodeVec[row].push_back(Node(sf::Vector2f((float)(midX + (row*TileWidth)), (float)(midY + (col*TileHeight)))));
//navGraph.addNode(Node(sf::Vector2f((float)(midX + (col*TileWidth)), (float)(midY + (row*TileHeight)))));

}
}

for (int row = 0; row < maxtileX; ++row) {
for (int col = 0; col < maxtileY; ++col) {
navGraph.addEdges(row, col);
}
}

}*/


/*void NavigationGraph::addEdges(int row, int col) {
int nodeX;
int nodeY;
sf::Vector2f thisNode;
sf::Vector2f neighborNode;
float distance;
for (int i = -1; i < 2; ++i) {
for (int j = -1; j < 2; ++j) {

if (i == 0 && j == 0) {

}
else if ((nodeY < numofTilesY) && (nodeY >= 0) && (nodeX < numofTilesX) && (nodeX >= 0)) {
thisNode = nodesList.at(row*numofTilesX + col).pos;
neighborNode = nodesList.at(nodeY*numofTilesX + nodeX).pos;

distance = TwoDistance(thisNode, neighborNode);

edgeList[row*numofTilesX + col].push_back(Edge(row*numofTilesX + col,
nodeY*numofTilesX + nodeX,
thisNode,
neighborNode,
distance));

}

}

}
}*/

/*
void NavigationGraph::AStar(NavigationGraph& graph, sf::Vector2f source, sf::Vector2f target) {

	std::priority_queue<std::pair<int, float>,
		std::vector< std::pair<int, float> >,
		Compare> pq;

	int sourceIndex = graph.PosToIndex(source.x, source.y);
	int targetIndex = graph.PosToIndex(target.x, target.y);
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
			//gif path
			return;
		}

		isValid[nextNode.first] = false;
		for (const auto& edge : graph.edgeList[nextNode.first]) {

			hCost = TwoDistance(target, graph.nodesList[edge.to].pos);
			rCost = realCost[nextNode.first] + edge.cost;

			if (realCost[edge.to] == -1) {
				heuristicCost[edge.to] = rCost + hCost;
				realCost[edge.to] = rCost;

				pq.push(std::make_pair(edge.to, rCost + hCost));

				graph.path[edge.to] = nextNode.first;

			}
			else if (realCost[edge.to] > rCost) {
				heuristicCost[edge.to] = rCost + hCost;
				realCost[edge.to] = rCost;

				graph.path[edge.to] = nextNode.first;

				pq.push(std::make_pair(edge.to, rCost + hCost));
			}

		}

	}


}*/