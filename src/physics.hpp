
//various calculations of acceleration, energy, etc.

#include "body.hpp"
#include "constants.hpp"

//retuns the distance squared between two positions
double squared_dist(double [DIM], double [DIM]);

//retuns the distance between two positions
double dist(double [DIM], double [DIM]);

//returns the acceleration on body 1 from body 2
double accel(Body&, Body&);
//calculates acceleration but with r raised to power 3 (instead of 2)
double accel_third_power(Body&, Body&);

//add acc on 1 from 2 to existing vector
void add_accel(Body&, Body&, double*);

//normalize a vector of given length (modifies vector)
double normalize(double*, int);
