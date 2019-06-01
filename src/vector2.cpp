#include "../include/vector2.hpp"

void Vector2::operator+= (const Vector2& vec2_2) {
    _x += vec2_2._x, _y += vec2_2._y;
}

void Vector2::operator-= (const Vector2& vec2_2) {
    _x -= vec2_2._x, _y -= vec2_2._y;
}

void Vector2::operator*= (const Vector2& vec2_2) {
    _x *= vec2_2._x, _y *= vec2_2._y;
}

void Vector2::operator/= (const Vector2& vec2_2) {
    _x /= vec2_2._x, _y /= vec2_2._y;
}


void Vector2::operator+= (float num) { _x += num, _y += num; }

void Vector2::operator-= (float num) { _x -= num, _y -= num; }

void Vector2::operator*= (float num) { _x *= num, _y *= num; }

void Vector2::operator/= (float num) { _x /= num, _y /= num; }


void Vector2::operator+= (int num_i) {
    float num = static_cast<float>(num_i);
    _x += num, _y += num;
}

void Vector2::operator-= (int num_i) {
    float num = static_cast<float>(num_i);
    _x -= num, _y -= num;
}

void Vector2::operator*= (int num_i) {
    float num = static_cast<float>(num_i);
    _x *= num, _y *= num;
}

void Vector2::operator/= (int num_i) {
    float num = static_cast<float>(num_i);
    _x /= num, _y /= num;
}


Vector2 operator+ (const Vector2& vec2_1, const Vector2& vec2_2) {
    return Vector2(vec2_1._x + vec2_2._x, vec2_1._y + vec2_2._y);
}

Vector2 operator- (const Vector2& vec2_1, const Vector2& vec2_2) {
    return Vector2(vec2_1._x - vec2_2._x, vec2_1._y - vec2_2._y);
}

Vector2 operator* (const Vector2& vec2_1, const Vector2& vec2_2) {
    return Vector2(vec2_1._x * vec2_2._x, vec2_1._y * vec2_2._y);
}

Vector2 operator/ (const Vector2& vec2_1, const Vector2& vec2_2) {
    return Vector2(vec2_1._x / vec2_2._x, vec2_1._y / vec2_2._y);
}


Vector2 operator+ (const Vector2& vec2_1, float num) {
    return Vector2(vec2_1._x + num, vec2_1._y + num);
}

Vector2 operator- (const Vector2& vec2_1, float num) {
    return Vector2(vec2_1._x - num, vec2_1._y - num);
}

Vector2 operator* (const Vector2& vec2_1, float num) {
    return Vector2(vec2_1._x * num, vec2_1._y * num);
}

Vector2 operator/ (const Vector2& vec2_1, float num) {
    return Vector2(vec2_1._x / num, vec2_1._y / num);
}


Vector2 operator+ (const Vector2& vec2_1, int num_i) {
    float num = static_cast<float>(num_i);
    return Vector2(vec2_1._x + num, vec2_1._y + num);
}

Vector2 operator- (const Vector2& vec2_1, int num_i) {
    float num = static_cast<float>(num_i);
    return Vector2(vec2_1._x - num, vec2_1._y - num);
}

Vector2 operator* (const Vector2& vec2_1, int num_i) {
    float num = static_cast<float>(num_i);
    return Vector2(vec2_1._x * num, vec2_1._y * num);
}

Vector2 operator/ (const Vector2& vec2_1, int num_i) {
    float num = static_cast<float>(num_i);
    return Vector2(vec2_1._x / num, vec2_1._y / num);
}



Vector2 operator+ (float num, const Vector2& vec2_1) {
    return Vector2(vec2_1._x + num, vec2_1._y + num);
}

Vector2 operator- (float num, const Vector2& vec2_1) {
    return Vector2(vec2_1._x - num, vec2_1._y - num);
}

Vector2 operator* (float num, const Vector2& vec2_1) {
    return Vector2(vec2_1._x * num, vec2_1._y * num);
}

Vector2 operator/ (float num, const Vector2& vec2_1) {
    return Vector2(vec2_1._x / num, vec2_1._y / num);
}


Vector2 operator+ (int num_i, const Vector2& vec2_1) {
    float num = static_cast<float>(num_i);
    return Vector2(vec2_1._x + num, vec2_1._y + num);
}

Vector2 operator- (int num_i, const Vector2& vec2_1) {
    float num = static_cast<float>(num_i);
    return Vector2(vec2_1._x - num, vec2_1._y - num);
}

Vector2 operator* (int num_i, const Vector2& vec2_1) {
    float num = static_cast<float>(num_i);
    return Vector2(vec2_1._x * num, vec2_1._y * num);
}

Vector2 operator/ (int num_i, const Vector2& vec2_1) {
    float num = static_cast<float>(num_i);
    return Vector2(vec2_1._x / num, vec2_1._y / num);
}



bool operator== (const Vector2& vec2_1, const Vector2& vec2_2) {
    return vec2_1.length() == vec2_2.length();
}

bool operator!= (const Vector2& vec2_1, const Vector2& vec2_2) {
    return vec2_1.length() != vec2_2.length();
}

bool operator>  (const Vector2& vec2_1, const Vector2& vec2_2) {
    return vec2_1.length() > vec2_2.length();
}

bool operator>= (const Vector2& vec2_1, const Vector2& vec2_2) {
    return vec2_1.length() >= vec2_2.length();
}

bool operator<  (const Vector2& vec2_1, const Vector2& vec2_2) {
    return vec2_1.length() < vec2_2.length();
}

bool operator<= (const Vector2& vec2_1, const Vector2& vec2_2) {
    return vec2_1.length() <= vec2_2.length();
}
