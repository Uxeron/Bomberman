#include "../include/gameLogic.hpp"

int main(int argc, char *args[]) {
	GameLogic* game = new GameLogic;
	game->startGame();
	game->mainLoop();
	game->stopGame();
	
	return 0; 
}
