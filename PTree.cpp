// Copyright 2024 Samuel Stanley

#include <map>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "SquareShape.hpp"
#include "PTree.hpp"

pTree::pTree(double L, int N, sf::Vector2f first_coords, float angle)
    : _L(L), _N(N) {
    // Create initial square as a template for all future squares
    SquareShape initial_square(_L);
    initial_square.setOutlineColor(sf::Color::Black);
    initial_square.setOutlineThickness(1);
    initial_square.setFillColor(sf::Color::White);
    initial_square.setPosition(first_coords);
    initial_square.setOrigin(0, initial_square.getSize().y);

    // Construct the tree from initial_square
    construct_tree(_N, angle, _tree, initial_square);
}

sf::Vector2f pTree::getMax() {
    // Get a point from _tree for a baseline for max values
    sf::Vector2f max = _tree.at(_N).front().getGlobalPoint(LOWER_LEFT);

    // Find max values of corners of squares in _tree
    for (auto v = _tree.begin(); v != _tree.end(); v++) {
        for (auto i = v->second.begin(); i != v->second.end(); i++) {
            for (CORNER corner = UPPER_LEFT; corner != INVALID; corner++) {
                sf::Vector2f coords = i->getGlobalPoint(corner);
                if (coords.x > max.x) max.x = coords.x;
                if (coords.y > max.y) max.y = coords.y;
            }
        }
    }
    return max;
}

sf::Vector2f pTree::getMin() {
    // Get a point from _tree for a baseline for max values
    sf::Vector2f min = _tree.at(_N).front().getGlobalPoint(LOWER_LEFT);

    // Find max values of corners of squares in _tree
    for (auto v = _tree.begin(); v != _tree.end(); v++) {
        for (auto i = v->second.begin(); i != v->second.end(); i++) {
            for (CORNER corner = UPPER_LEFT; corner != INVALID; corner++) {
                sf::Vector2f coords = i->getGlobalPoint(corner);
                if (coords.x < min.x) min.x = coords.x;
                if (coords.y < min.y) min.y = coords.y;
            }
        }
    }
    return min;
}

sf::Vector2f pTree::getSize() {
    sf::Vector2f max = getMax(), min = getMin();
    return sf::Vector2f(max.x - min.x, max.y - min.y);
}

sf::Vector2f pTree::getPosition() {
    return _tree.at(_N).front().getGlobalPoint(LOWER_LEFT);
}

void pTree::setPosition(float x, float y) {
    float x_dif;
    float y_dif;

    // Calculate the difference every square's position should be subtracted by
    x_dif = _tree.at(_N).front().getPosition().x - x;
    y_dif = _tree.at(_N).front().getPosition().y - y;

    // Set positions of every square in _tree
    for (auto v = _tree.begin(); v != _tree.end(); v++) {
        for (auto i = v->second.begin(); i != v->second.end(); i++) {
            float new_x = i->getPosition().x - x_dif;
            float new_y = i->getPosition().y - y_dif;
            i->setPosition(new_x, new_y);
        }
    }
}

void pTree::construct_tree(int N, float angle, _pTree& tree, SquareShape square) {
    // Insert to tree
    tree[N].push_back(square);

    // Recursively call construct_tree for two children
    if (N > 0) {
        // Create left_child from square
        SquareShape left_child = square;
        left_child.setSize(square.getSize().x * cos(toRadians(angle)));
        left_child.setOrigin(0, left_child.getSize().y);
        left_child.setPosition(square.getGlobalPoint(UPPER_LEFT));
        left_child.setRotation(square.getRotation() - angle);

        // Create right_child from square
        SquareShape right_child = square;
        right_child.setSize(square.getSize().x * sin(toRadians(angle)));
        right_child.setOrigin(0, right_child.getSize().y);
        right_child.setPosition(left_child.getGlobalPoint(LOWER_RIGHT));
        right_child.setRotation(square.getRotation() + 90 - angle);

        // Call construct_tree from children
        construct_tree(N - 1, angle, tree, left_child);
        construct_tree(N - 1, angle, tree, right_child);
    }
}

void pTree::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto v = _tree.begin(); v != _tree.end(); v++) {
        for (auto i = v->second.begin(); i != v->second.end(); i++) {
            target.draw(*i, states);
        }
    }
}
