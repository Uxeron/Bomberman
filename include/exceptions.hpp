#pragma once

#include <sstream>

class SDL_init_error : public std::runtime_error {
   public:
    SDL_init_error() : runtime_error("SDL failed to initialize") {}
};

class SDL_Image_init_error : public std::runtime_error {
   public:
    SDL_Image_init_error() : runtime_error("SDL Image failed to initialize") {}
};

class window_error : public std::runtime_error {
   public:
    window_error() : runtime_error("Failed to create a window") {}
};

class surface_error : public std::runtime_error {
   public:
    surface_error() : runtime_error("Failed to get surface from window") {}
};

class file_not_found_error : public std::runtime_error {
    std::string m_message;

   public:
    file_not_found_error(const char* filename) : runtime_error(filename) {
        std::stringstream ss;
        ss << "file not found " << filename;
        m_message = ss.str();
    }

    const char* what() const noexcept { return m_message.c_str(); }
};

class map_read_error : public std::runtime_error {
    std::string m_message;

   public:
    map_read_error(int x, int y) : runtime_error("") {
        std::stringstream ss;
        ss << "invalid map symbol at line " << x << ", position " << y;
        m_message = ss.str();
    }

    const char* what() const noexcept { return m_message.c_str(); }
};
