#include "Game.h"

Game::Game()
{
	this->window = nullptr;
	this->videoMode = sf::VideoMode(800, 600);

	this->InitWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::PollEvents()
{
	while (this->window->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	this->PollEvents();
}

/*
	Renders game objects
*/
void Game::Render()
{
	this->window->clear(sf::Color::Red);

	// Draw game

	this->window->display();
}

const bool Game::Running() const
{
	return this->window->isOpen();
}

void Game::InitVariables()
{
}

void Game::InitWindow()
{
	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
}
