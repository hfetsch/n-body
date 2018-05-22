
#include "constants.hpp"
#include <stddef.h>

#include "body.hpp"

//
class Region{

    public:
        //coordinates of center
        double coords [DIM];
        //half of a side length
        double half_length;
        //array of sub-regions (nullptr when there are none)
        Region* children [CHILDREN];
        //center-of-mass of the region
        Body* com;
        //new body position in this region
        Body* new_com;

        //used to decide whether we should switch com and new_com
        bool parity;

        //list of bodies to add later
        std::list<Body> add_queue;

        //returns true if the region contains this point
        bool contains(double [DIM]);

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
       std::list<Body> update(std::list<Body>&); //IMPLEMENT

       //Constructor: (coords, half_length, parity)
       Region(double*, double, bool);
};
