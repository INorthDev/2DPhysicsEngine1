#include "libs/SFML-2.5.1/include/SFML/Window.hpp"
#include "libs/SFML-2.5.1/include/SFML/Graphics.hpp"
#include "libs/vector2d.h"
#include <iostream>
#include <exception>
#include <cmath>

using namespace sf;

typedef Vector2D<float> vec;

int main() {

    RenderWindow window;
    window.create(VideoMode(800, 600), "Physics Engine");
    window.setFramerateLimit(60);


    Vector2<int> pos = Mouse::getPosition();
    vec v1 = vec(pos);

    Texture texture;
    if(!texture.loadFromFile("/home/ahmet/CLionProjects/2DPhysicsEngine1/assets/arrow.png")) {
        cout << "can't load texture" << endl;
    }

    Sprite vector;
    vector.setTexture(texture);
    vector.setPosition(0.0, 0.0);
    vector.setRotation(0.0);

    while(window.isOpen()) {

        Event event{};

        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::Black);

        v1.update(Mouse::getPosition());

        vector.setRotation(v1.getAngle());

        window.draw(vector);

        window.display();

    }


    return 0;
}