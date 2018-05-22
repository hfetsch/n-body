
#include "tree.hpp"
#include <stddef.h>

using namespace std;
using namespace math;

//Constructor
Region::Region(double* p, double hl, bool par)
:parity{par}, half_length{hl}, children{nullptr}
{
    for(int i = 0; i < DIM; ++i) {
        coords[i] = p[i];
    }
}

//return whether this region contains the given point
bool Region::contains(double* pos) {
    //if any coordinate is more than a half length away from the center, return false
    for(int i = 0; i < DIM; ++i) {
        if(abs(pos[i] - coords[i]) > half_length)
            return false;
    }
    return true;
}

//update velocity and position, and move bodies between regions
        /*
        -recurse down until the region has only 1 body
            -starting from the top of the tree, calculate acceleration contributions
                -while recursing down, push add_queue items as appropriate
            -update velocity of body
            -calculate new position:
                -if new position is in this region, set new_com to new postion
                -else, set new_com to nullptr and return new body position
        -if we have subregions:
            -for each subregion:
                -push items in add_queue as appropriate
                -add returned bodies to the add_queue
            -calculate new_com, factoring in each body in add_queue that is in this region
        */
list<Body> Region::update(list<Body>& bodies) {

}