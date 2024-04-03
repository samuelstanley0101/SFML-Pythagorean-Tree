// Copyright 2024 Samuel Stanley

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

enum CORNER { UPPER_LEFT = 0, UPPER_RIGHT = 1, LOWER_RIGHT = 2, LOWER_LEFT = 3, INVALID = 4 };

class SquareShape : public sf::RectangleShape {
 public:
    // Construct a SquareShape with side length L
    explicit SquareShape(float L) : sf::RectangleShape(sf::Vector2f(L, L)) {}

    // Set the size of the square from a single float
    void setSize(float size);

    // Get the global coordinates of the corner of a SquareShape. If corner is not a valid value,
    // std::invalid_argument will be thrown
    sf::Vector2f getGlobalPoint(CORNER corner);
};

void operator++(CORNER& corner, int unused);

inline float toDegrees(float radians) {
    return radians * 180 / M_PI;
}
inline float toRadians(float degrees) {
    return degrees * M_PI / 180;
}
