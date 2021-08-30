#include "Game.h"

int main() {
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
