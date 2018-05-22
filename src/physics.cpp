
//various calculations of acceleration, energy, etc.

#include "body.hpp"
#include "constants.hpp"
#include <cmath>

using namespace std;
using namespace math;

//retuns the distance squared between two positions
double squared_dist(double [DIM] p1, double [DIM] p2){
    double sum = 0;
    for(short i = 0; i < DIM; ++i) {
        sum += pow(p1[i] - p2[i], 2);
    }
    return sum;
}
//retuns the distance between two positions
double dist(double [DIM] p1, double [DIM] p2) {
    return pow(squared_dist(p1, p2), 0.5);
}


//returns the acceleration on body 1 from body 2
double accel(Body& b1, Body& b2) {
    return b2.mass * G / squared_dist(b1.coords, b2.coord);
}

