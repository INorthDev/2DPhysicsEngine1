//
// Created by can on 23.10.2022.
//

#ifndef INC_2DPHYSICSENGINE1_VECTOR2D_H
#define INC_2DPHYSICSENGINE1_VECTOR2D_H
#include <cmath>
#include <string>
#include <iostream>


using namespace std;

class Vector2D {

    double magnitude;
    double angle;
    double cartesian[2]{};

    string direction;

    void updateCartesian() {
        cartesian[0] = magnitude*cos(angle);
        cartesian[1] = magnitude*sin(angle);
    }

    void updateDirection() { //this function updates direction value with 4 digit precision
        switch ((int)(fmod(angle, 2*M_PI)*180.00000/M_PI)) {
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

    Vector2D(double _m, double _a) {
        magnitude = _m, angle = _a * M_PI / 180.0;
        updateDirection(), updateCartesian();
    }

    [[nodiscard]] string getDirection() const { return direction; }

    [[nodiscard]] double getMagnitude() const { return magnitude; }

    [[nodiscard]] double getAngleAsRadians() const { return angle; }

    [[nodiscard]] double getAngle() const { return angle/M_PI*180.0; }

    double* getCartesian() { return cartesian; }

    void setAngle(double _a) {
        angle = _a / 180.0 * M_PI;
        updateCartesian();
        updateDirection();
    }

    void turnLeft(double _a) {
        angle += _a/180.0*M_PI;
        updateCartesian();
        updateDirection();
    }

    void turnRight(double _a) {
        angle -= _a / 180.0 * M_PI;
        updateCartesian();
        updateDirection();
    }

    void setMagnitude(double _m) {
        cartesian[0] = cartesian[0] * _m / magnitude;
        cartesian[1] = cartesian[1] * _m / magnitude;
        magnitude = _m;
    }

    void changeMagnitude(double _m) {
        cartesian[0] = cartesian[0]*(_m / magnitude + 1);
        cartesian[1] = cartesian[1]*(_m / magnitude + 1);
        magnitude += _m;
    }

    static double crossProduct(const Vector2D& v1, const Vector2D& v2) {
        return v1.magnitude*v2.magnitude*sin(v1.angle > v2.angle ? v1.angle-v2.angle : v2.angle-v1.angle);
    }

    static double dotProduct(const Vector2D& v1, const Vector2D& v2) {
        return v1.magnitude*v2.magnitude*cos(v1.angle > v2.angle ? v1.angle-v2.angle : v2.angle-v1.angle);
    }

    static int isEqual(const Vector2D& v1, const Vector2D& v2) {
        return v1.magnitude == v2.magnitude && v1.angle == v2.angle;
    }

    friend Vector2D operator + (const Vector2D& v1, const Vector2D& v2) {
        double y = v1.cartesian[1]+v2.cartesian[1];
        double _a = (180.0 / M_PI) * (atan2(y, (v1.cartesian[0] + v2.cartesian[0])) + M_PI * (double)(y < 0.0));
        double _m = sqrt(pow(v1.magnitude, 2) + pow(v2.magnitude, 2) + 2 * v1.magnitude * v2.magnitude * cos(fmod(v1.angle, 2 * M_PI) - fmod(v2.angle, 2 * M_PI)));
        return {_m, _a};

    }

    friend Vector2D operator - (const Vector2D& v1, const Vector2D& v2) {
        return v1+(-1.0*v2);
    }

    friend double operator / (const Vector2D& v1, const Vector2D& v2) {
        return crossProduct(v1, v2);
    }

    friend Vector2D operator / (double _c, const Vector2D& v) {
        return {v.magnitude/abs(_c), fmod(v.angle + M_PI*(double)(_c<0.0), 2*M_PI)};
    }

    friend double operator * (const Vector2D& v1, const Vector2D& v2) {
        return dotProduct(v1, v2);
    }

    friend Vector2D operator * (double _c, const Vector2D& v) {
        return {abs(_c)*v.magnitude, fmod(v.angle + M_PI*(double)(_c<0.0), 2*M_PI)};
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
        o << "  angle = " << v.angle/M_PI*180.0 << "   ";
        o << "  cartesian coords = (" << v.cartesian[0] << ", " << v.cartesian[1] << ")   ";
        o << "  direction = " << v.direction << "]" << endl;
        return o;
    }

};

#endif //INC_2DPHYSICSENGINE1_VECTOR2D_H
