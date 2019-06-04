#include "../include/menuItem.hpp"

MenuItem::MenuItem(int ind, SDL_Surface* spr, TTF_Font* fnt, const char* pth, Window& wind)
    : index(ind), sprite(spr), font(fnt), path(pth), window(wind) {
    loadMap();
    writeName();
    drawIcon();
};

void MenuItem::writeName() {
    // Get map name from map file path
    std::string mapName = std::string(path);
    std::size_t len = mapName.find_last_of('.');
    len -= 5;
    if (len > 15) len = 15; // Limit name length to 15 characters
    mapName = mapName.substr(5, len);

    // Render the text
    SDL_Surface* text = TTF_RenderText_Shaded(font, mapName.c_str(), fgCol, bgCol);

    // Draw the text on the sprite
    SDL_Rect textLocation = { textPos.x(), textPos.y(), 0, 0 };
    SDL_BlitSurface(text, NULL, sprite, &textLocation);
    SDL_FreeSurface(text);
}

void MenuItem::drawIcon() {
    int scale;
    if (mapSize.x() > 25 || mapSize.y() > 25) scale = 2;
    else scale = 4;

    Vector2 iconPos = Vector2((100 - mapSize.x() * scale) / 2,
                              (100 - mapSize.y() * scale) / 2);

    // Lock the surface
    if (SDL_MUSTLOCK(sprite)) {
        SDL_LockSurface(sprite);
    }

    int charCount = 0;

    for (int y1 = 0; y1 < mapSize.y(); y1++) {
        for (int x1 = 0; x1 < mapSize.x(); x1++) {
            if (map[y1][x1] > 3) throw map_read_error(y1, x1);
            if (map[y1][x1] == 3) if(++charCount > 4) throw too_many_characters_error(path);
            for (int y2 = 0; y2 < scale; y2++) {
                for (int x2 = 0; x2 < scale; x2++) {
                    drawPixel(sprite, iconPos.x() + x1 * scale + x2, iconPos.y() + y1 * scale + y2, mapColors[map[y1][x1]]);
                }
            }
        }
    }

    // Unlock surface
    if (SDL_MUSTLOCK(sprite)) {
        SDL_UnlockSurface(sprite);
    }
}

void MenuItem::loadMap() { 
    std::ifstream mapFile;
    mapFile.open(path);
    if (!mapFile.is_open()) throw file_not_found_error(path);

    int number;
    mapFile >> number;
    mapSize.x(number);
    mapFile >> number;
    mapSize.y(number);

    if (mapSize.x() < 13) throw map_too_small_error(path);
    if (mapSize.x() > 50) throw map_too_large_error(path);

    if (mapSize.y() < 9) throw map_too_small_error(path);
    if (mapSize.y() > 50) throw map_too_large_error(path);

    for (int y = 0; y < mapSize.y(); y++) {
        map.push_back(std::vector<int> ());
        for (int x = 0; x < mapSize.x(); x++) {
            mapFile >> number;
            map[y].push_back(number);

            if (mapFile.eof() && (y < mapSize.y() || x < mapSize.x())) 
                throw map_size_error(path);
        }
    }
};

void MenuItem::drawPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    // Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    // Set the pixel
    pixels[(y * surface->w) + x] = pixel;
}
