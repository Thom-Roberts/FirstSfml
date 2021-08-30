#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
/*
	Acts as game engine
*/
class Game
{
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

public:

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
};

