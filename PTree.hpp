// Copyright 2024 Samuel Stanley

#pragma once

#include <map>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "SquareShape.hpp"

typedef std::map<int, std::vector<SquareShape>> _pTree;

class pTree : public sf::Drawable {
 public:
    // Construct a pTree with square side length L, recursion depth N, and coordinates of the
    // lower left corner of the first square first_coords
    pTree(double L, int N, sf::Vector2f first_coords, float angle);

    // Get the greatest x and y coordinates occupied by the tree
    sf::Vector2f getMax();

    // Get the least x and y coordinates occupied by the tree
    sf::Vector2f getMin();

    // Get the size of the box which surrounds the tree
    sf::Vector2f getSize();

    // Get the position of the lower left corner of the first square of the tree
    sf::Vector2f getPosition();

    // Set the position of the lower left corner first square of the tree to (x, y) and adjust
    // all other squares accordingly
    void setPosition(float x, float y);
    // Set the position of the lower left corner first square of the tree to position and adjust
    // all other squares accordingly
    inline void setPosition(const sf::Vector2f &position) {
        setPosition(position.x, position.y);
    }

 private:
    // Recursively construct a pTree's map from a recursion depth N, a base rotation angle, an
    // empty map tree, and a base SquareShape (which will be inserted at depth N) square
    static void construct_tree(int N, float angle, _pTree& tree, SquareShape square);

    // Draw every SquareShape in _tree to target
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

    const double _L;
    const int _N;
    _pTree _tree;
};
