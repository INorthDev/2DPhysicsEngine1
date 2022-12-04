//
// Created by ahmet on 20.11.2022.
//

#ifndef INC_2DPHYSICSENGINE1_ENTITY_H
#define INC_2DPHYSICSENGINE1_ENTITY_H
#include "SFML-2.5.1/include/SFML/Window.hpp"
#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include "force.h"
#include "vector2d.h"
#include <iostream>
#include <exception>
#include <cmath>
#include "calc.h"
#include "physictime.h"

using namespace std;
using namespace sf;

typedef Vector2D<float> Vec;

class Entity {
    Vec location;
    Vec acceleration;
    Vec velocity;
    function<float(float)> accelerationXFunc;
    float mass{};
    Sprite sprite;
    Texture texture;
public:
    Entity(Vec _location, float _mass, const Texture& _texture, float angle): location(std::move(_location)), acceleration(0.0, angle), velocity(0.0, angle), texture(_texture), sprite(_texture), accelerationXFunc(std::move([](float){ return 0; })) {
        sprite.setPosition(location.xAxis(), location.yAxis());
    }
    Entity(Vec _location, float _mass, const Texture& _texture, float angle, const function<float(float)>& func): location(std::move(_location)), acceleration(0.0, angle), velocity(0.0, angle), texture(_texture), sprite(_texture), accelerationXFunc(func) {
        sprite.setPosition(location.xAxis(), location.yAxis());
    }
    Vec getLocation() { return location; }
    Vec getAcceleration() { return acceleration; }
    Vec getVelocity() { return velocity; }
    float getMass() const { return mass; }
    Sprite getSprite() { return sprite; }
    Texture getTexture() { return texture; }

    void update() {
        acceleration.setXComponent(accelerationXFunc(t));
        acceleration.setYComponent(0.5*10*t*t);
        velocity = velocity + change*acceleration;
        location = location + change*velocity;
        sprite.setPosition(location.xAxis(), location.yAxis());
        sprite.setScale(0.1, 0.1);
    }
};

#endif //INC_2DPHYSICSENGINE1_ENTITY_H
