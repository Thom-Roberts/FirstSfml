#pragma once

#include <iostream>
#include <vector>
// Init random
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
/*
	Acts as game engine
*/
class Game
{
// Functions
public:
	Game();
	virtual ~Game();

	void Update();
	void Render();
	const bool Running() const;
	

private:
	void InitVariables();
	void InitWindow();
	void PollEvents();
	void InitEnemies();
	void UpdateMousePositions();
	void SpawnEnemy();
	
	void UpdateEnemies();
	void RenderEnemies();

// Variables
public:

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::RectangleShape enemy;

	// Mouse positions in window
	sf::Vector2i mousePosWindow;

	std::vector<sf::RectangleShape> enemies;

	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	int points;
};

