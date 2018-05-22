
#include "body.hpp"

//Constructor
//takes an array of size DIM and a mass
Body::Body(double* p, double m) 
:mass{m}
{
    for(int i = 0; i < DIM; ++i) {
        pos[i] = p[i];
        vel[i] = 0;
    }
}

//Constructor
//takes pos and vel arrays of size DIM, and a mass
Body::Body(double* p, double* v, double m) 
:mass{m}
{
    for(int i = 0; i < DIM; ++i) {
        pos[i] = p[i];
        vel[i] = v[i];
    }
}