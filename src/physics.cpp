
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

//calculates acceleration, but raises r to third power
//avoids having to normalize distance vector
double accel_third_power(Body& b1, Body& b2) {
    return b2.mass * G / pow(squared_dist(b1.coords, b2.coords), 1.5);
}

//TODO: can optimize further to remove one division

//calculate the acceleration on body 1 from body 2
//then add this to acceleration vector acc
void add_accel(Body& b1, Body& b2, double* acc) {
    //calculate magnitude of acceleration
    //includes extra 1/r factor to normalize vector
    double mag = accel_third_power(b1, b2);

    //get difference between bodies' positions
    //  and divide by magnitude
    //then add to the given acceleration vector
    for(int i = 0; i < DIM; ++i) {
        acc[i] += (b2.coords[i] - b1.coords[i]) / mag;
    }
}

//normalize a vector of length len (modifies vector)
double normalize(double* vec, int len) {
    //get the vector's magnitude
    double mag = 0;
    for(int i = 0; i < len; ++i) {
        mag += pow(vec[i], 2);
    }
    mag = pow(mag, 0.5);

    //divide every element by the magnitude
    for(int i = 0; i < len; ++i) {
        vec[i] /= mag;
    }
}