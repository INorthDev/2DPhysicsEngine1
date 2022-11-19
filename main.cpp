#include "libs/SFML-2.5.1/include/SFML/Window.hpp"
#include "libs/SFML-2.5.1/include/SFML/Graphics.hpp"
#include "libs/force.h"
#include "libs/vector2d.h"
#include <iostream>
#include <exception>
#include <cmath>
#include "libs/calc.h"

using namespace sf;

typedef Vector2D<float> Vec;

double a(double i) {
    return i*i-i-1.0;
}

int main() {


    ////Window Setup////
    RenderWindow window;
    window.create(VideoMode(960, 640), "Physics Engine");
    window.setFramerateLimit(60);
    ////Window Setup End////

    ////Mouse Vector Setup////
    Vec mouse = Vec(Mouse::getPosition());
    Vec mouseNotional = mouse;
    ////Mouse Vector Setup End////

    ////Texture Setup////
    Texture texture;
    if(!texture.loadFromFile("/home/ahmet/CLionProjects/2DPhysicsEngine1/assets/arrow.png")) {
        cout << "can't load texture" << endl;
    }
    ////Texture Setup End////

    Sprite mousePointer = Sprite(texture);
    mousePointer.setPosition(250.0, 250.0);
    Vec arrow = Vec(mousePointer.getPosition());
    mousePointer.setOrigin(0.0, 13.0);

    ////Window Loop////
    while(window.isOpen()) {

        ////Event Check////
        Event event{};
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
        }
        ////Event Check End////

        mouse.update(Mouse::getPosition());

        arrow.update(mousePointer.getPosition());

        mouseNotional = mouse-arrow;

        mousePointer.setRotation(mouseNotional.getAngle());
        mousePointer.setScale(mouseNotional.getMagnitude()/160, 1.0);


        window.clear(Color::Black);

        window.draw(mousePointer);

        auto re = integrate<double>(0.0, 5.0, &a);

        cout << re << endl;

        window.display();

    }
    ////Window Loop End////

    return 0;
}