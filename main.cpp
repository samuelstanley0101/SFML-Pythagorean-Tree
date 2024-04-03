// Copyright 2024 Samuel Stanley

#include <iostream>
#include <string>
#include <exception>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "SquareShape.hpp"
#include "PTree.hpp"

int main(int argc, char* argv[]) {
    // Throw an exception if arguments for L and N are not provided
    if (argc < 3)
        throw std::invalid_argument("Error: insufficient arguments");

    // Process command line arguments
    double L = std::stod(argv[1]);
    int N = std::stoi(argv[2]);
    float angle = 45;
    if (argc >= 4)
        angle = std::stof(argv[3]);

    // Create Pythagorian Tree
    pTree tree(L, N, sf::Vector2f(0, 0), angle);
    sf::Vector2f coords;
    coords.x = ceil(tree.getPosition().x - tree.getMin().x);
    coords.y = ceil(tree.getPosition().y - tree.getMin().y);
    tree.setPosition(coords);

    // Create window
    sf::Vector2f window_size = tree.getSize();
    sf::VideoMode mode(ceil(window_size.x), ceil(window_size.y));
    sf::RenderWindow window(mode, "Pythagorian Tree");

    // Render tree
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.draw(tree);
        window.display();
    }

    return 0;
}
