#include <iostream>
#include "libs/vector2d.h"
//#include <SFML/Window.hpp>

using namespace std;

typedef Vector2D vec;

int main() {
    //sf::Window window(sf::VideoMode(800, 600), "2D Physics");

    vec A = vec(5, 37);

    vec B = vec(4, 180);

    vec C = vec(3, -90);

    cout << A << B << C << A-B << A+B << A+B+C << A+C << A-C;

    return 0;
}
