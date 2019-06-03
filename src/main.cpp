#include "../include/gameLogic.hpp"
#include "../include/menu.hpp"

int main(int argc, char *args[]) {
	std::unique_ptr<GameLogic> game;

	try {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) // Start SDL
			throw SDL_init_error();

		if (IMG_Init(IMG_INIT_PNG) == 0)   // Start SDL_img
			throw SDL_Image_init_error();

		auto menu = std::make_unique<Menu>();
		game = menu->menuLoop();
		while (game != NULL) {
			game->startGame();
			game->mainLoop();
			game->stopGame();

			auto menu = std::make_unique<Menu>();
			game = menu->menuLoop();
		}
	} catch (const std::exception& e) {
		std::cout << "error: " << e.what() << std::endl;
	} 
	
	SDL_Quit(); // Quit SDL
    IMG_Quit(); // Quit SDL_img

	return 0; 
}
