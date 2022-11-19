//
// Created by ahmet on 19.11.2022.
//

#ifndef INC_2DPHYSICSENGINE1_CALC_H
#define INC_2DPHYSICSENGINE1_CALC_H

using namespace std;

template<class T>
T riemann_sum(function<T(T)> func, T _a, T _b, int n) {
    T _dx = (_b-_a)/(T)n;
    T sum = 0.0;
    for(int i = 1; i <= n; i++) {
        T _x = _a+_dx*(T)i-_dx/(T)2.0;
        sum += func(_x)*_dx;
    }
    return sum;
}

template<class T>
T riemann_left_sum(function<T(T)> func, T _a, T _b, int n) {
    T _dx = (_b-_a)/(T)n;
    T sum = 0.0;
    for(int i = 1; i <= n; i++) {
        T _x = _a+_dx*(T)(i-1);
        sum += func(_x)*_dx;
    }
    return sum;
}

template<class T>
T riemann_right_sum(function<T(T)> func, T _a, T _b, int n) {
    T _dx = (_b-_a)/(T)n;
    T sum = 0.0;
    for(int i = 1; i <= n; i++) {
        T _x = _a+_dx*(T)i;
        sum += func(_x)*_dx;
    }
    return sum;
}

template<class T>
T integrate(function<T(T)> func, T _a, T _b) {
    return riemann_sum<T>(func, _a, _b, (int)((T)(_b-_a)/(T)(0.001)));
}

template<class T>
T differentiate(function<T(T)> func, T _a, T _b) {
    return (func(_b)-func(_a))/(_b-_a);
}

#endif //INC_2DPHYSICSENGINE1_CALC_H
