#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "libs/vector2d.h"

int main() {

    sf::Window window;
    window.create(sf::VideoMode(800, 600), "A Window");


    return 0;
}