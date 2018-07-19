#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map2D.hpp"
#include <string>
#include "Player.hpp"
#include <cmath>


		



int main()
{

	bool drawNavGraph = false;
	bool drawVision = true;
	int maxWidth = 600;
	int maxHeight = 480;
	

	sf::ConvexShape visionPoly;
	visionPoly.setPointCount(20);
	visionPoly.setFillColor(sf::Color::Red);

	// create the window
	sf::RenderWindow window(sf::VideoMode(maxWidth, maxHeight), "Window");
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(false);
	Map2D map;
	float PI = 3.14159;


	sf::CircleShape p1(3);
	sf::CircleShape p2(7);
	



	p1.setFillColor(sf::Color::Blue);

	p2.setFillColor(sf::Color::Green);



	sf::Clock clock;
	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Cant read arial \n";
	}
	//map.addDrawable(wall1);
	//map.addDrawable(wall2);


	//sf::VertexArray segments = sf::VertexArray();



	//ADD WALLS INTO MAP
	std::vector<sf::Vector2f> segments = std::vector<sf::Vector2f>();

	map.addWall(sf::Vector2f(0, 0), sf::Vector2f(maxWidth, 0), sf::Vector2f(maxWidth, 1), sf::Vector2f(0, 1));

	map.addWall(sf::Vector2f(0, 0), sf::Vector2f(0, maxHeight), sf::Vector2f(1, maxHeight), sf::Vector2f(1, 0));

	map.addWall(sf::Vector2f(0, maxHeight), sf::Vector2f(maxWidth, maxHeight), sf::Vector2f(maxWidth, maxHeight-1), sf::Vector2f(0, maxHeight - 1));

	map.addWall(sf::Vector2f(maxWidth, maxHeight), sf::Vector2f(maxWidth, 0), sf::Vector2f(maxWidth-1, 0), sf::Vector2f(maxWidth - 1, maxHeight));

	map.addWall(sf::Vector2f(50, 50), sf::Vector2f(150, 50), sf::Vector2f(150, 100), sf::Vector2f(50, 100));

	map.addWall(sf::Vector2f(250, 250), sf::Vector2f(400, 250), sf::Vector2f(400, 150), sf::Vector2f(250, 150));


	for (auto it = map.walls.begin(); it < map.walls.end(); ++it) {
		segments.push_back(it->A);
		segments.push_back(it->B);
		segments.push_back(it->C);
		segments.push_back(it->D);
	}


	//Create Navigation Graph from the map
	map.buildGraph(580, 460, 40, 30);

	//Remove edges that leads to walls
	map.clearEdges();


	//NAVIGATION TEST
	int startIndex = map.navGraph.PosToIndex(200, 150);
	int distance;
	int targetIndex = map.navGraph.PosToIndex(10, 10);
	


	std::vector<sf::Vector2f> intersectionPoints = std::vector<sf::Vector2f>();

	while (window.isOpen())
	{
		intersectionPoints.clear();


		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(146, 142, 142));

		


		if (drawNavGraph) {
			sf::CircleShape c(2);

			for (const auto& node : map.navGraph.nodesList) {
				text.setPosition(node.pos);
				text.setCharacterSize(15);
				text.setFillColor(sf::Color::Red);

			}



			for (const auto& list : map.navGraph.edgeList) {
				for (const auto& edge : list) {
					sf::Vertex line[] =
					{
						sf::Vertex(edge.fromPos),
						sf::Vertex(edge.toPos)
					};
					window.draw(line, 2, sf::Lines);

				}
			}

		}

		
	

		

		//player1.Update();
		//player1.myPathfinder.movealongPath();
		
		window.draw(map);

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		//visionPoly.setPoint(0, sf::Vector2f(mousePos.x, mousePos.y));

		if (drawVision) {
			sf::Vector2f intersectionPoint;
			float dx;
			float dy;
			float distance;
			sf::Vertex line[2];
			int count = 0;
			for (float angle = PI/2; angle < PI ; angle += (PI / 2 ) / 50) {
				dx = std::cos(angle);
				dy = std::sin(angle);
				float distance;
				//std::cout << "x : " << mousePos.x + dx << " y : " << mousePos.y + dy << std::endl;
				if (map.getClosestWallIntersect(sf::Vector2f(mousePos.x, mousePos.y), sf::Vector2f(mousePos.x + dx, mousePos.y + dy), distance, intersectionPoint)) {
					line[0].position = sf::Vector2f(mousePos.x, mousePos.y);
					p1.setPosition(intersectionPoint.x, intersectionPoint.y);
					//visionPoly.setPoint( count, intersectionPoint);
					//visionPoly[count].color = sf::Color::Red;
					//++count;

					line[1].position = p1.getPosition();
					window.draw(line, 2, sf::Lines);
					window.draw(p1);
				}
			}
		}
		//visionPoly.setPoint(51, sf::Vector2f(mousePos.x, mousePos.y));
		//window.draw(visionPoly);




		//std::cout << "x : " << mousePos.x << " y : " << mousePos.y << std::endl;

		
	

		window.display();



	}




	return 0;
}




//////////////// old stuff

/*
std::cout << map.navGraph.nodesList[startIndex].posX << " , " << map.navGraph.nodesList[startIndex].posY << "\n";
std::cout << map.navGraph.nodesList[targetIndex].posX << " , " << map.navGraph.nodesList[targetIndex].posY << "\n";
std::cout << "\n";
for (auto elem = map.navGraph.path[startIndex]; elem != targetIndex; elem = map.navGraph.path[elem]) {
p1.setPosition(map.navGraph.nodesList[elem].pos);
window.draw(p1);
std::cout << map.navGraph.nodesList[elem].posX << " , " << map.navGraph.nodesList[elem].posY << "\n";
}*/

// run the program as long as the window is open

//Player player1(map.navGraph);


//player1.setGraph(map.navGraph);
//player1.setPosition(sf::Vector2f(10, 10));
//player1.myPathfinder.setPath(map.navGraph.path);
//player1.myPathfinder.setPath(map.navGraph.path);
//player1.myPathfinder.path.push_back(sf::Vector2f(150, 150));




//Player player1(map.navGraph);
//player1.Move(sf::Vector2f(150, 150));
//player1.getPosition();
