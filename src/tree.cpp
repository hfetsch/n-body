
#include "tree.hpp"
#include <stddef.h>

using namespace std;
using namespace math;

//Default Constructor (should only be used in main)
Region::Region();

//Constructor
Region::Region(double* p, double hl, bool par)
:parity{par}, half_length{hl}, children{nullptr}
{
    //set initial coordinates
    for(int i = 0; i < DIM; ++i) {
        coords[i] = p[i];
    }

    //set the subregions to nullptr for now
    for(int i = 0; i < CHILDREN; ++i) {
        children[i] = nullptr;
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
    //first switch the parity of com if necessary
    if(parity == COUNTER % 2) {
        Body* temp = com;
        com = new_com;
        delete temp; //note: may fail silently if temp is nullptr but that's fine
        parity = !parity;
    }

    //add the bodies we were passed to the queue
    add_queue.merge(bodies);

    //decide whether there are subregions
    if(children[0] == nullptr) { //case: no children
        switch(add_queue.size()) {
            case 0: //no bodies to add
                if(com == nullptr) { //if there's no body, do nothing
                    new_com = nullptr;
                } else { //otherwise, update the body
                    //if new_com is null, create it
                    //inital properties are unimportant, and will be set
                    if(new_com == nullptr)
                        new_com = new Body();

                    update_body(com);
                }
                break; //now we're done
            case 1: //one body to add
                if(com == nullptr) { //if the region was empty, add and update the body
                    update_body(add_queue.front(), new_com);
                    add_queue.pop_front();
                } else { //otherwise, add the current body to add_queue and split
                    add_queue.push(*com);
                    split();
                }
                break;
            default: //multiple bodies to add
                //if there was a com, push it to the add_queue
                if(com != nullptr) {
                    add_queue.push(*com);
                }
                //now split into subregions
                split();
        }
    } else { //case: children exist

    }
}

//update body using pos/vel/mass of old
double* Region::update_body(Body& old, Body& body) {


}

void Region::split() {

}