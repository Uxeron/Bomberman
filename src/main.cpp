#include "../include/gameLogic.hpp"

int main(int argc, char *args[]) {
	GameLogic* game = new GameLogic;

	try {
		game->startGame();
		game->mainLoop();
	} catch (const std::exception& e) {
		std::cout << "error: " << e.what() << std::endl;
	} 
	game->stopGame();

	delete game;

	return 0; 
}
