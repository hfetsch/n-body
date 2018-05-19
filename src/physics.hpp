
//various calculations of acceleration, energy, etc.

#include "body.hpp"
#include "constants.hpp"

//retuns the distance squared between two positions
double squared_dist(double [DIM], double [DIM]);
//retuns the distance between two positions
double dist(double [DIM], double [DIM]);
//returns the acceleration on body 1 from body 2
double accel(Body&, Body&);


