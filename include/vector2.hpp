#pragma once

#include <cmath>

class Vector2 {
  private:
    float _x;
    float _y;

  public:
    Vector2() : _x(0), _y(0) {};
    Vector2(float x, float y) : _x(x), _y(y) {};
    Vector2(int x, int y) : _x(static_cast<float>(x)), _y(static_cast<float>(y)) {};

    int length() const { return sqrt(_x * _x + _y * _y); }

    float xFull() const { return _x; }
    float yFull() const { return _y; }

    int x() const { return static_cast<int>(_x); }
    int y() const { return static_cast<int>(_y); }

    void x(float newX) { _x = newX; }
    void y(float newY) { _y = newY; }

    void x(int newX) { _x = static_cast<float>(newX); }
    void y(int newY) { _y = static_cast<float>(newY); }

    Vector2 operator+= (const Vector2& vec2_2);
    Vector2 operator-= (const Vector2& vec2_2);
    Vector2 operator*= (const Vector2& vec2_2);
    Vector2 operator/= (const Vector2& vec2_2);

    Vector2 operator+= (float num);
    Vector2 operator-= (float num);
    Vector2 operator*= (float num);
    Vector2 operator/= (float num);

    Vector2 operator+= (int num_i);
    Vector2 operator-= (int num_i);
    Vector2 operator*= (int num_i);
    Vector2 operator/= (int num_i);

    friend Vector2 operator+ (const Vector2& vec2_1, const Vector2& vec2_2);
    friend Vector2 operator- (const Vector2& vec2_1, const Vector2& vec2_2);
    friend Vector2 operator* (const Vector2& vec2_1, const Vector2& vec2_2);
    friend Vector2 operator/ (const Vector2& vec2_1, const Vector2& vec2_2);


    friend Vector2 operator+ (const Vector2& vec2_1, float num);
    friend Vector2 operator- (const Vector2& vec2_1, float num);
    friend Vector2 operator* (const Vector2& vec2_1, float num);
    friend Vector2 operator/ (const Vector2& vec2_1, float num);

    friend Vector2 operator+ (const Vector2& vec2_1, int num_i);
    friend Vector2 operator- (const Vector2& vec2_1, int num_i);
    friend Vector2 operator* (const Vector2& vec2_1, int num_i);
    friend Vector2 operator/ (const Vector2& vec2_1, int num_i);

    friend Vector2 operator+ (float num, const Vector2& vec2_1);
    friend Vector2 operator- (float num, const Vector2& vec2_1);
    friend Vector2 operator* (float num, const Vector2& vec2_1);
    friend Vector2 operator/ (float num, const Vector2& vec2_1);

    friend Vector2 operator+ (int num_i, const Vector2& vec2_1);
    friend Vector2 operator- (int num_i, const Vector2& vec2_1);
    friend Vector2 operator* (int num_i, const Vector2& vec2_1);
    friend Vector2 operator/ (int num_i, const Vector2& vec2_1);


    // All comparison operators check the length of the vectors
    friend bool operator== (const Vector2& vec2_1, const Vector2& vec2_2);
    friend bool operator!= (const Vector2& vec2_1, const Vector2& vec2_2);

    friend bool operator>  (const Vector2& vec2_1, const Vector2& vec2_2);
    friend bool operator>= (const Vector2& vec2_1, const Vector2& vec2_2);
    friend bool operator<  (const Vector2& vec2_1, const Vector2& vec2_2);
    friend bool operator<= (const Vector2& vec2_1, const Vector2& vec2_2);
};
