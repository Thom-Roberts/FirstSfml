#include "Game.h"

Game::Game()
{
	this->InitVariables();
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

void Game::Update()
{
	this->PollEvents();

	this->UpdateMousePositions();
	
	this->UpdateEnemies();
}

/*
	Renders game objects
*/
void Game::Render()
{
	this->window->clear();

	// Draw game
	this->RenderEnemies();
	this->window->display();
}

const bool Game::Running() const
{
	return this->window->isOpen();
}

void Game::UpdateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::SpawnEnemy()
{
	// Position from 0 to max width (without enemy going out of bounds)
	float randomX = (float)(rand() % (int)(this->window->getSize().x - this->enemy.getSize().x));
	this->enemy.setPosition(randomX, 0.f);
	
	this->enemy.setFillColor(sf::Color::Green);
	this->enemies.push_back(this->enemy);

	// Remove enemies that are off the screen
}

void Game::UpdateEnemies()
{
	// Spawn enemy and update timer
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->SpawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}

	// Move enemies downwards
	for (auto& e : this->enemies) {
		e.move(0.f, 1.f);
	}
}

void Game::RenderEnemies()
{
	for (auto& e : this->enemies) {
		this->window->draw(e);
	}
}

void Game::InitVariables()
{
	this->window = nullptr;
	this->videoMode = sf::VideoMode(800, 600);
	
	enemySpawnTimerMax = 1000.f;
	enemySpawnTimer = enemySpawnTimerMax;
	maxEnemies = 5;
	points = 0;
}

void Game::InitWindow()
{
	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
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