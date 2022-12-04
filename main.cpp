#include "libs/SFML-2.5.1/include/SFML/Window.hpp"
#include "libs/SFML-2.5.1/include/SFML/Graphics.hpp"
#include "libs/force.h"
#include "libs/vector2d.h"
#include <iostream>
#include <exception>
#include <cmath>
#include "libs/calc.h"
#include "libs/entity.h"
#include "libs/physictime.h"

using namespace std;
using namespace sf;

typedef Vector2D<float> Vec;

int main() {
    ////Window Setup////
    RenderWindow window;
    window.create(VideoMode(960, 640), "Physics Engine");
    window.setFramerateLimit(FPS_LIM);
    ////Window Setup End////

    ////Mouse Vector Setup////
    Vec mouse = Vec(Mouse::getPosition());
    ////Mouse Vector Setup End////

    ///Texture Setup///

    Texture ball_t;
    if(!ball_t.loadFromFile("/home/ahmet/CLionProjects/2DPhysicsEngine1/assets/ball.png")) { cout << "can't load ball texture"; }

    ///Texture Setup End///

    ///Sprite Setup///

    Entity Ball = Entity(Vec(0, 0), 5.0, ball_t, 0.0, [](float i){ return t*100; });

    ///Sprite Setup End////

    ////Window Loop////
    while(window.isOpen()) {
        t++;
        ////Event Check////
        Event event{};
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
        }
        ////Event Check End////
        mouse.update(Mouse::getPosition());
        Ball.update();
        window.clear(Color::Black);
        window.draw(Ball.getSprite());
        window.display();
    }
    ////Window Loop End////

    return 0;
}