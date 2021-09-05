#pragma once

#include <iostream>
#include <vector>
#include <sstream>
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
	void InitFonts();
	void InitText();
	void UpdateMousePositions();
	void SpawnEnemy();
	
	void UpdateEnemies();
	void RenderEnemies(sf::RenderTarget& target);

	void UpdateText();
	void RenderText(sf::RenderTarget& target);
	
// Variables
public:
	bool endGame;

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::RectangleShape enemy;

	// Mouse positions in window
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	std::vector<sf::RectangleShape> enemies;

	sf::Font font;
	sf::Text uiText;

	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int32_t maxEnemies;
	uint32_t points;
	int32_t health;
	bool mouseHeld;

	
};

