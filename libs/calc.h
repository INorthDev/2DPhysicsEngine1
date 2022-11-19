//
// Created by ahmet on 19.11.2022.
//

#ifndef INC_2DPHYSICSENGINE1_CALC_H
#define INC_2DPHYSICSENGINE1_CALC_H
#define change 0.01

template<class T>
T integrate(T _s, T _e, T(*func)(T)) {
    T area = 0;
    for(T i = _s+change; i < _e; i += change) {
        area += func(i)*change;
    }
    return area;
}

#endif //INC_2DPHYSICSENGINE1_CALC_H
