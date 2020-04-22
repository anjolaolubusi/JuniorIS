#ifndef MMAS_H
#define MMAS_H

#include "Ant.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class MMAS{
private:
	GraphMap graphMap;
	std::vector<std::shared_ptr<Ant>> ants;
	int ant_count = 10;
	bool StartHasBeenSet = false;
	bool EndHasBeenSet = false;
	int inter_num = 0;
	int antAtEnd = 0;
	bool hasBegun = false;

	float radius = 50.0f;

	std::vector<sf::Sprite> ListOfNodes;
	std::vector<sf::RectangleShape> ListOfEdges;
	sf::Texture nodeTex;
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	void initWindow();

public:
	MMAS();
	MMAS(int startX, int startY, int endX, int endY, int number_of_ants);
	MMAS( const MMAS& otherAnt);

	
	void updateDt();

	void updateSFMLEvents();
	void update();
	void render();
	void run();

	void AddNode(const int x, const int y);
	void AddEdge(const int x1, const int y1, const int x2, const int y2);
	void AddEdge(const PheroKey& key);	
	void RemoveEdge(const PheroKey& key);
	void SetStartNode(const int x, const int y);
	void SetEndNode(const int x, const int y);
	void SetNumberOfAnts(const int number_of_ants);
	void PrintPheroTable();
	void StartAlgorithm();
	~MMAS();
};

#endif
