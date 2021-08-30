#include "Game.h"

Game::Game()
{
	this->window = nullptr;
	this->videoMode = sf::VideoMode(800, 600);
	
	this->InitWindow();
	this->InitEnemies();
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

void Game::InitEnemies()
{
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

void Game::Update()
{
	this->PollEvents();

	// Update mouse position
	std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;
}

/*
	Renders game objects
*/
void Game::Render()
{
	this->window->clear();

	// Draw game
	this->window->draw(this->enemy);

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
	this->window->setFramerateLimit(144);
}
