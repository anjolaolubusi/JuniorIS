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

//Struct to represent Edge of Graph
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
	std::vector<std::shared_ptr<Ant>> ants; //Ants of the graph
	int ant_count = 30; //Number of ants
	bool StartHasBeenSet = false; //Boolean to determine show the if the Start Node has been set
	bool EndHasBeenSet = false; //Boolean to determine show the if the End Node has been set
	int inter_num = 0; //Iteration Number
	int antAtEnd = 0; //Number of ants at the end node
	bool hasBegun = false; //Boolean to determine if the ACO has begun
	float PheroConst = 0.5; //Value of Pheromone Constant
	float SnowProb = 0.1; //Value of Snow Probability
	bool BeginCanadianSnow = false; //Boolean that represents if the Canadian Traveller has begun
	bool HasSnowed = false; //Boolean that represents if the Canadian Traveller has begun

	std::vector<sf::Sprite> ListOfNodes; //List of Nodes
	std::vector<PheroEdge> ListOfEdges; //List of Edges
	sf::Texture nodeTex; //Texture of the node
	sf::RenderWindow* window; //Window Objects
	sf::Event sfEvent; //Event objects (Handle all window events)
	sf::View view; //Handles current viewspace

	sf::Clock dtClock; //Measures cpu clock
	float dt; // Holds the time between frames

	void initWindow(); //Initializes the window
public:
	MMAS(); //Default Constructor
	MMAS(int startX, int startY, int endX, int endY, int number_of_ants); //Parameterized Constructor
	MMAS( const MMAS& otherAnt);//Copy Constructor

	void updateDt(); //Calculate the time between frames

	void updateSFMLEvents(); //Handles window events
	void update(); //Updates the ACO algorithm
	void render(); //Renders objects to screen
	void run(); // Simulator loop

	void AddNode(const int x, const int y); //Add node to graph
	void AddEdge(const int x1, const int y1, const int x2, const int y2); //Add Edge to graph
	void AddEdge(const PheroKey& key);//Add Edge to graph
	void RemoveEdge(const PheroKey& key); //Remove Edge from graph
	void SetStartNode(const int x, const int y); //Sets Start Node
	void SetEndNode(const int x, const int y); //Set End Node
	void SetNumberOfAnts(const int number_of_ants); //Sets the number of ants
	void PrintPheroTable(); //Prints all the edges of the graph
	void HandleGUI(); //Handles Menu Items
	void StartAlgorithm(); //Starts the ACO algorithm
	bool HasBestPathBeenFound(); //Returns boolean value that represents if the best path has been found
	void UpdatePathColours(); //Updates the colours of the path
	~MMAS();

};

#endif
