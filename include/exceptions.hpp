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

class SDL_TTF_init_error : public std::runtime_error {
   public:
    SDL_TTF_init_error() : runtime_error("SDL TTF failed to initialize") {}
};

class window_error : public std::runtime_error {
   public:
    window_error() : runtime_error("Failed to create a window") {}
};

class surface_error : public std::runtime_error {
   public:
    surface_error() : runtime_error("Failed to get surface from window") {}
};

class object_missing_error : public std::runtime_error {
   public:
    object_missing_error() : runtime_error("Object not found in list") {}
};



class too_many_characters_error : public std::runtime_error {
   public:
    std::string m_message;

    too_many_characters_error(const char* filename) : runtime_error(filename) {
        std::stringstream ss;
        ss << "too many characters found in " << filename << ", maximum is 4";
        m_message = ss.str();
    }

    const char* what() const noexcept { return m_message.c_str(); }
};

class file_not_found_error : public std::runtime_error {
   public:
    std::string m_message;

    file_not_found_error(const char* filename) : runtime_error(filename) {
        std::stringstream ss;
        ss << "file not found " << filename;
        m_message = ss.str();
    }

    const char* what() const noexcept { return m_message.c_str(); }
};

class map_read_error : public std::runtime_error {
   public:
    std::string m_message;

    map_read_error(int x, int y) : runtime_error("") {
        std::stringstream ss;
        ss << "invalid map symbol at line " << x << ", position " << y;
        m_message = ss.str();
    }

    const char* what() const noexcept { return m_message.c_str(); }
};

class map_size_error : public std::runtime_error {
   public:
    std::string m_message;

    map_size_error(const char* filename) : runtime_error(filename) {
        std::stringstream ss;
        ss << "map " << filename << " is of incorrect size";
        m_message = ss.str();
    }

    const char* what() const noexcept { return m_message.c_str(); }
};

class map_too_small_error : public std::runtime_error {
   public:
    std::string m_message;

    map_too_small_error(const char* filename) : runtime_error(filename) {
        std::stringstream ss;
        ss << "map " << filename << " is too small, minimum size is 13x9";
        m_message = ss.str();
    }

    const char* what() const noexcept { return m_message.c_str(); }
};

class map_too_large_error : public std::runtime_error {
   public:
    std::string m_message;

    map_too_large_error(const char* filename) : runtime_error(filename) {
        std::stringstream ss;
        ss << "map " << filename << " is too large, maximum size is 50x50";
        m_message = ss.str();
    }

    const char* what() const noexcept { return m_message.c_str(); }
};
