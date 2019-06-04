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



class error_base : public std::runtime_error {
  public:
    std::stringstream ss;

    error_base(const char* filename) : runtime_error(filename) {};

    const char* what() const noexcept { return ss.str().c_str(); }
};

class too_many_characters_error : public error_base {
   public:
    too_many_characters_error(const char* filename) : error_base(filename) {
        ss << "too many characters found in " << filename << ", maximum is 4";
    }
};

class file_not_found_error : public error_base {
   public:
    file_not_found_error(const char* filename) : error_base(filename) {
        ss << "file not found " << filename;
    }
};

class map_read_error : public error_base {
   public:
    map_read_error(int x, int y) : error_base("") {
        ss << "invalid map symbol at line " << x << ", position " << y;
    }
};

class map_size_error : public error_base {
   public:
    map_size_error(const char* filename) : error_base(filename) {
        ss << "map " << filename << " is of incorrect size";
    }
};
