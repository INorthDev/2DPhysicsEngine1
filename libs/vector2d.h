//
// Created by can on 23.10.2022.
//

#ifndef INC_2DPHYSICSENGINE1_VECTOR2D_H
#define INC_2DPHYSICSENGINE1_VECTOR2D_H
#include <cmath>
#include <string>
#include <iostream>


using namespace std;

template<class T>
class Vector2D {

    T magnitude;
    T angle;
    T cartesian[2]{};

    string direction;

    void updateCartesian() {
        cartesian[0] = magnitude*cos(angle);
        cartesian[1] = magnitude*sin(angle);
    }

    void updateDirection() { //this function updates direction value with 4 digit precision
        switch ((int)(fmod(angle, 2*((T)M_PI))*180.00000/((T)M_PI))) {
            case 00000: {direction = "East"; break;}
            case 450000: {direction = "NorthEast"; break;}
            case 900000: {direction = "North"; break;}
            case 1350000: {direction = "NorthWest"; break;}
            case 1800000: {direction = "West"; break;}
            case 2250000: {direction = "SouthWest"; break;}
            case 2700000: {direction = "South"; break;}
            case 3150000: {direction = "SouthEast"; break;}
            default: {direction = "Unknown"; break;}
        }
    }

public:

    Vector2D(T _m, T _a) {
        magnitude = _m, angle = _a * ((T)M_PI) / 180.0;
        updateDirection(), updateCartesian();
    }

    explicit Vector2D(sf::Vector2<int> vector2) {
        auto _x = (T) vector2.x;
        auto _y = (T) vector2.y;
        magnitude = sqrt(_x*_x+_y*_y), angle = atan2(_y, _x) + ((T)M_PI) * (T)(_y < 0.0);
        updateDirection(), updateCartesian();
    }

    [[nodiscard]] string getDirection() const { return direction; }

    [[nodiscard]] T getMagnitude() const { return magnitude; }

    [[nodiscard]] T getAngleAsRadians() const { return angle; }

    [[nodiscard]] T getAngle() const { return angle/((T)M_PI)*180.0; }

    T* getCartesian() { return cartesian; }

    void update(sf::Vector2<int> vector2) {
        auto _x = (T) vector2.x;
        auto _y = (T) vector2.y;
        magnitude = sqrt(_x*_x+_y*_y), angle = atan2(_y, _x) + ((T)M_PI) * (T)(_y < 0.0);
        updateDirection(), updateCartesian();
    }

    void setAngle(T _a) {
        angle = _a / 180.0 * ((T)M_PI);
        updateCartesian();
        updateDirection();
    }

    void turnLeft(T _a) {
        angle += _a/180.0*((T)M_PI);
        updateCartesian();
        updateDirection();
    }

    void turnRight(T _a) {
        angle -= _a / 180.0 * ((T)M_PI);
        updateCartesian();
        updateDirection();
    }

    void setMagnitude(T _m) {
        cartesian[0] = cartesian[0] * _m / magnitude;
        cartesian[1] = cartesian[1] * _m / magnitude;
        magnitude = _m;
    }

    void changeMagnitude(T _m) {
        cartesian[0] = cartesian[0]*(_m / magnitude + 1);
        cartesian[1] = cartesian[1]*(_m / magnitude + 1);
        magnitude += _m;
    }

    static T crossProduct(const Vector2D& v1, const Vector2D& v2) {
        return v1.magnitude*v2.magnitude*sin(v1.angle > v2.angle ? v1.angle-v2.angle : v2.angle-v1.angle);
    }

    static T dotProduct(const Vector2D& v1, const Vector2D& v2) {
        return v1.magnitude*v2.magnitude*cos(v1.angle > v2.angle ? v1.angle-v2.angle : v2.angle-v1.angle);
    }

    static int isEqual(const Vector2D& v1, const Vector2D& v2) {
        return v1.magnitude == v2.magnitude && v1.angle == v2.angle;
    }

    friend Vector2D operator + (const Vector2D& v1, const Vector2D& v2) {
        T y = v1.cartesian[1]+v2.cartesian[1];
        T _a = (180.0 / ((T)M_PI)) * (atan2(y, (v1.cartesian[0] + v2.cartesian[0])) + ((T)M_PI) * (T)(y < 0.0));
        T _m = sqrt(pow(v1.magnitude, 2) + pow(v2.magnitude, 2) + 2 * v1.magnitude * v2.magnitude * cos(fmod(v1.angle, 2 * ((T)M_PI)) - fmod(v2.angle, 2 * ((T)M_PI))));
        return {_m, _a};

    }

    friend Vector2D operator - (const Vector2D& v1, const Vector2D& v2) {
        return v1+(-1.0*v2);
    }

    friend T operator / (const Vector2D& v1, const Vector2D& v2) {
        return crossProduct(v1, v2);
    }

    friend Vector2D operator / (T _c, const Vector2D& v) {
        return {v.magnitude/abs(_c), fmod(v.angle + ((T)M_PI)*(T)(_c<0.0), 2*((T)M_PI))};
    }

    friend T operator * (const Vector2D& v1, const Vector2D& v2) {
        return dotProduct(v1, v2);
    }

    friend Vector2D operator * (T _c, const Vector2D& v) {
        return {abs(_c)*v.magnitude, fmod(v.angle + ((T)M_PI)*(T)(_c<0.0), 2*((T)M_PI))};
    }

    friend int operator == (const Vector2D& v1, const Vector2D& v2) {
        return isEqual(v1, v2);
    }

    friend int operator != (const Vector2D& v1, const Vector2D& v2) {
        return !isEqual(v1, v2);
    }

    friend ostream& operator << (ostream& o, const Vector2D& v) {
        o << "Vector2D: " << &v << " = ";
        o << "[ magnitude = " << v.magnitude << "   ";
        o << "  angle = " << v.angle/((T)M_PI)*180.0 << "   ";
        o << "  cartesian coords = (" << v.cartesian[0] << ", " << v.cartesian[1] << ")   ";
        o << "  direction = " << v.direction << "]" << endl;
        return o;
    }

};

#endif //INC_2DPHYSICSENGINE1_VECTOR2D_H
