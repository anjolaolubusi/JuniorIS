#ifndef MMAS_H
#define MMAS_H

#include "imgui.h"
#include "imgui-SFML.h"

#include "Ant.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

struct PheroEdge{
    float x1;
    float y1;
    float x2;
    float y2;
	sf::RectangleShape line;
	PheroEdge(const PheroEdge& otherPE){
	x1 = otherPE.x1;
	x2 = otherPE.x2;
	y1 = otherPE.y1;
	y2 = otherPE.y2;
	line = otherPE.line;
	}
	PheroEdge(){
    x1 = -1;
    x2 = -1;
    y1 = -1;
    y2 = -1;
	}
};

class MMAS{
private:
	GraphMap graphMap;
	std::vector<std::shared_ptr<Ant>> ants;
	int ant_count = 30;
	bool StartHasBeenSet = false;
	bool EndHasBeenSet = false;
	int inter_num = 0;
	int antAtEnd = 0;
	bool hasBegun = false;
	float radius = 50.0f;
	float PheroConst = 0.5;

	std::vector<sf::Sprite> ListOfNodes;
	std::vector<PheroEdge> ListOfEdges;
	sf::Texture nodeTex;
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::View view;

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
	void HandleGUI();
	void StartAlgorithm();
	bool HasBestPathBeenFound();
	void UpdatePathColours();
	~MMAS();
};

#endif
