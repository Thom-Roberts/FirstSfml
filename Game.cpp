#include "Game.h"

Game::Game()
{
	this->InitVariables();
	this->InitFonts();
	this->InitText();
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

	if (!endGame) {
		this->UpdateMousePositions();
	
		this->UpdateText();

		this->UpdateEnemies();
	}

	if (health <= 0)
		endGame = true;
}

/*
	Renders game objects
*/
void Game::Render()
{
	this->window->clear();

	// Draw game
	this->RenderEnemies(*window);
	this->RenderText(*window);
	this->window->display();
}

const bool Game::Running() const
{
	return this->window->isOpen();
}

void Game::UpdateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(mousePosWindow);
}

void Game::SpawnEnemy()
{
	// Position from 0 to max width (without enemy going out of bounds)
	float randomX = (float)(rand() % (int)(this->window->getSize().x - this->enemy.getSize().x));
	this->enemy.setPosition(randomX, 0.f);
	
	// Randomize enemy type
 	int32_t type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setFillColor(sf::Color::Magenta);
		this->enemy.setSize(sf::Vector2f(20.f, 20.f));
		break;
	case 1:
		this->enemy.setFillColor(sf::Color::Blue);
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		break;
	case 2:
		this->enemy.setFillColor(sf::Color::Cyan);
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		break;
	case 3:
		this->enemy.setFillColor(sf::Color::Red);
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		break;
	case 4:
		this->enemy.setFillColor(sf::Color::Green);
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		break;
	default:
		this->enemy.setFillColor(sf::Color::Yellow);
		this->enemy.setSize(sf::Vector2f(200.f, 200.f));
		break;
	}

	this->enemies.push_back(this->enemy);
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
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].move(0.f, 2.f);
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			enemies.erase(enemies.begin() + i);
			health -= 1;
			std::cout << "Health: " << this->health << std::endl;
		}
	}

	// Check if clicked on
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!mouseHeld) {
			mouseHeld = true;
			bool deleted = false;

			for (size_t i = 0; i < enemies.size() && deleted == false; i++) {
				if (enemies[i].getGlobalBounds().contains(this->mousePosView)) {
					deleted = true;
					auto enemy = enemies[i];
					if (enemy.getFillColor() == sf::Color::Magenta)
						points += 10;
					else if (enemy.getFillColor() == sf::Color::Blue) {
						points += 7;
					}
					else if (enemy.getFillColor() == sf::Color::Cyan) {
						points += 5;
					}
					else if (enemy.getFillColor() == sf::Color::Red) {
						points += 3;
					}
					else if (enemy.getFillColor() == sf::Color::Green) {
						points++;
					}

					
					enemies.erase(enemies.begin() + i);
				}
			}
		}
	}
	else {
		mouseHeld = false;
	}
}

void Game::RenderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies) {
		target.draw(e);
	}
}

void Game::UpdateText()
{
	std::stringstream ss;
	ss << "Points: " << points << std::endl;
	ss << "Health: " << health << std::endl;
	uiText.setString(ss.str());
}

void Game::RenderText(sf::RenderTarget& target)
{
	target.draw(uiText);
}

void Game::InitVariables()
{
	this->window = nullptr;
	this->videoMode = sf::VideoMode(800, 600);
	
	enemySpawnTimerMax = 15.f;
	enemySpawnTimer = enemySpawnTimerMax;
	maxEnemies = 10;
	points = 0;
	health = 20;
	mouseHeld = false;
	endGame = false;
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
	this->enemy.setFillColor(sf::Color::Cyan);
}

void Game::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
		std::cout << "ERROR::GAME::INTIFONTS::Failed to load font!" << std::endl;
	}
}

void Game::InitText()
{
	uiText.setFont(font);
	uiText.setCharacterSize(24);
	uiText.setFillColor(sf::Color::White);
	uiText.setString("NONE");
}
