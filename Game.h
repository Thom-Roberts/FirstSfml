#pragma once

#include <iostream>

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

// Variables
public:

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::RectangleShape enemy;
};

