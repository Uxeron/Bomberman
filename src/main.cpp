#include "../include/main.hpp"

int main(int argc, char *args[]) {
	try {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) // Start SDL
			throw SDL_init_error();

		if (IMG_Init(IMG_INIT_PNG) == 0)   // Start SDL_img
			throw SDL_Image_init_error();

		if (TTF_Init() != 0)	// Start SDL_ttf
			throw SDL_TTF_init_error();

		while (true) {
			std::unique_ptr<GameLogic> game;
			{
			auto menu = std::make_unique<Menu>();
			game = menu->menuLoop();
			if (game == NULL) break;
			}
			game->startGame();
			game->mainLoop();
			game->stopGame();
		}
	} catch (const std::exception& e) {
		std::cout << "error: " << e.what() << std::endl;
	} 
	
	SDL_Quit(); // Quit SDL
    IMG_Quit(); // Quit SDL_img
	TTF_Quit(); // Quit SDL_ttf

	return 0; 
}
