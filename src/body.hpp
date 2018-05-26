
#ifndef BODY_HPP_INCLUDED
#define BODY_HPP_INCLUDED true

#include "constants.hpp"

class Body {

    public:
        //coordinates
        double pos [DIM];
        //velocity
        double vel [DIM];
        //mass
        double mass;

        //Constructor: no parameters
        //everything initialized to 0
        Body();
        //Constructor: (position, mass)
        //default initial velocity 0
        Body(double*, double);
        //Constructor: (position, velocity, mass)
        Body(double*, double*, double);
    
};

#endif