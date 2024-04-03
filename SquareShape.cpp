// Copyright 2024 Samuel Stanley

#include <cmath>
#include <exception>
#include <SFML/Graphics.hpp>

#include "SquareShape.hpp"

void SquareShape::setSize(float size) {
    RectangleShape::setSize(sf::Vector2f(size, size));
}

sf::Vector2f SquareShape::getGlobalPoint(CORNER corner) {
    // Variables used by every corner
    float sinTheta = sin(toRadians(getRotation()));
    float cosTheta = cos(toRadians(getRotation()));
    float x_distance;
    float y_distance;
    sf::Vector2f coords = getPosition();

    // Different corners' global coordinates require different equations
    switch (corner) {
        case UPPER_LEFT:
        x_distance = getOrigin().x;
        y_distance = getOrigin().y;
        coords.x += y_distance * sinTheta - x_distance * cosTheta;
        coords.y -= x_distance * sinTheta + y_distance * cosTheta;
        break;
        case UPPER_RIGHT:
        x_distance = getSize().x - getOrigin().x;
        y_distance = getOrigin().y;
        coords.x += x_distance * cosTheta + y_distance * sinTheta;
        coords.y -= y_distance * cosTheta - x_distance * sinTheta;
        break;
        case LOWER_RIGHT:
        x_distance = getSize().x - getOrigin().x;
        y_distance = getSize().y - getOrigin().y;
        coords.x += x_distance * cosTheta - y_distance * sinTheta;
        coords.y -= -y_distance * cosTheta - x_distance * sinTheta;
        break;
        case LOWER_LEFT:
        x_distance = getOrigin().x;
        y_distance = getSize().y - getOrigin().y;
        coords.x += -y_distance * sinTheta - x_distance * cosTheta;
        coords.y -= x_distance * sinTheta - y_distance * cosTheta;
        break;
        default:
            throw std::invalid_argument("SquareShape::getGlobalPoint");
    }
    return coords;
}

void operator++(CORNER& corner, int unused) {
    switch (corner) {
        case UPPER_LEFT: corner = UPPER_RIGHT;
        break;
        case UPPER_RIGHT: corner = LOWER_RIGHT;
        break;
        case LOWER_RIGHT: corner = LOWER_LEFT;
        break;
        default: corner = INVALID;
        break;
    }
}
