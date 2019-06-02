#include "../include/gameLogic.hpp"

int main(int argc, char *args[]) {
	auto game = std::make_unique<GameLogic>();

	try {
		game->startGame();
		game->mainLoop();
	} catch (const std::exception& e) {
		std::cout << "error: " << e.what() << std::endl;
	} 
	game->stopGame();

	return 0; 
}
