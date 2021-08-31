#include "Game.h"

int main() {
	// Init srand
	std::srand((unsigned)time(NULL));

	// Init game engine
	Game game;

	while (game.Running()) {
		// Update
		game.Update();
		// Render
		game.Render();
	}

	return 0;
}
