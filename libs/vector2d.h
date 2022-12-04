//
// Created by can on 23.10.2022.
//

#ifndef INC_2DPHYSICSENGINE1_VECTOR2D_H
#define INC_2DPHYSICSENGINE1_VECTOR2D_H
#include <cmath>
#include <string>
#include <iostream>
#define PI M_PI


using namespace std;

template<class T>
class Vector2D {

    T magnitude;
    T angle;
    T cartesian[2]{};

    string direction;

    void updateAngle() { angle = (T) atan2f((float)cartesian[1], (float)cartesian[0]); }

    void updateCartesian() { cartesian[0] = magnitude*cos(angle), cartesian[1] = magnitude*sin(angle); }

    void updateDirection() { //this function updates direction value with 4 digit precision
        switch ((int)(fmod(angle, 2*PI)*180.00000/PI)) {
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
        magnitude = _m, angle = _a * PI / 180.0;
        updateDirection(), updateCartesian();
    }

    explicit Vector2D(sf::Vector2<T> vector2) {
        auto _x = (T) vector2.x, _y = (T) vector2.y;
        magnitude = sqrt(_x*_x+_y*_y), angle = atan2(_y, _x);
        updateDirection(), updateCartesian();
    }

    explicit Vector2D(sf::Vector2<int> vector2) {
        auto _x = (T) vector2.x, _y = (T) vector2.y;
        magnitude = sqrt(_x*_x+_y*_y), angle = atan2(_y, _x);
        updateDirection(), updateCartesian();
    }

    [[nodiscard]] string getDirection() const { return direction; }

    [[nodiscard]] T getMagnitude() const { return magnitude; }

    [[nodiscard]] T getAngleAsRadians() const { return angle; }

    [[nodiscard]] T getAngle() const { return (T)(angle/PI*180.0); }

    T* getCartesian() { return cartesian; }

    T xAxis() { return cartesian[0]; }
    T yAxis() { return cartesian[1]; }

    void update(sf::Vector2<T> vector2) {
        auto _x = (T) vector2.x, _y = (T) vector2.y;
        magnitude = sqrt(_x*_x+_y*_y), angle = (T)atan2((double)_y, (double)_x);
        updateDirection(), updateCartesian();
    }

    void update(sf::Vector2<int> vector2) {
        auto _x = (T) vector2.x, _y = (T) vector2.y;
        magnitude = sqrt(_x*_x+_y*_y), angle = (T)atan2((double)_y, (double)_x);
        updateDirection(), updateCartesian();
    }

    void setAngle(T _a) {
        angle = _a / 180.0 * PI;
        updateCartesian(), updateDirection();
    }

    void turnLeft(T _a) {
        angle += _a/180.0*PI;
        updateCartesian(), updateDirection();
    }

    void turnRight(T _a) {
        angle -= _a / 180.0 * PI;
        updateCartesian(), updateDirection();
    }

    void setMagnitude(T _m) {
        magnitude = _m;
        updateCartesian();
    }

    void changeMagnitude(T _m) {
        magnitude += _m;
        updateCartesian();
    }

    void setXComponent(T _m) {
        cartesian[0] = _m;
        magnitude = (T)sqrtf((float)(_m*_m+cartesian[1]*cartesian[1]));
        updateAngle(), updateDirection();
    }

    void setYComponent(T _m) {
        cartesian[1] = _m;
        magnitude = (T)sqrtf((float)(_m*_m+cartesian[0]*cartesian[0]));
        updateAngle(), updateDirection();
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
        T _a = (180.0 / PI) * (atan2(v1.cartesian[1]+v2.cartesian[1], (v1.cartesian[0] + v2.cartesian[0]))), _m = sqrt(v1.magnitude*v1.magnitude + v2.magnitude*v2.magnitude + 2 * v1.magnitude * v2.magnitude * cos((T)fmod((double)(v1.angle-v2.angle), 2*M_PI)));
        return {_m, _a};
    }

    friend Vector2D operator - (const Vector2D& v1, const Vector2D& v2) {
        return v1+(-1.0*v2);
    }

    friend T operator / (const Vector2D& v1, const Vector2D& v2) {
        return crossProduct(v1, v2);
    }

    friend Vector2D operator / (T _c, const Vector2D& v) {
        return {v.magnitude/abs(_c), fmod(v.angle + PI*(T)(_c<0.0), 2*PI)};
    }

    friend T operator * (const Vector2D& v1, const Vector2D& v2) {
        return dotProduct(v1, v2);
    }

    friend Vector2D operator * (T _c, const Vector2D& v) {
        return {abs(_c)*v.magnitude, (T)(180.0/PI*(T)(fmod((T)v.angle + PI*(T)(_c<0.0), 2*PI)))};
    }

    friend int operator == (const Vector2D& v1, const Vector2D& v2) {
        return isEqual(v1, v2);
    }

    friend int operator != (const Vector2D& v1, const Vector2D& v2) {
        return !isEqual(v1, v2);
    }

    friend ostream& operator << (ostream& o, const Vector2D& v) {
        o << "Vector2D: " << &v << " = " << "[ magnitude = " << v.magnitude << "   " << "  angle = " << v.angle/PI*180.0 << "   " << "  cartesian coords = (" << v.cartesian[0] << ", " << v.cartesian[1] << ")   " << "  direction = " << v.direction << "]" << endl;
        return o;
    }

};

static Vector2D<float> ZeroVector = Vector2D<float>(0.0, 0.0);

#endif //INC_2DPHYSICSENGINE1_VECTOR2D_H
