
#include "tree.hpp"
#include "physics.hpp"
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
void Region::update() {
    //first, switch the parity of COM if neccessary
    check_parity();

    

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

//update new_com based on children and add_queue
void Region::update_com() {
    //initialize new_com as a new body
    if(new_com == nullptr) {
        new_com = new Body{};
    } else {
        new_com = Body{};
    }

    //add each child's new_com, weighted by mass
    for(int i = 0; i < CHILDREN; ++i) {
        new_com -> mass += children[i]->new_com->mass;
        for(int j = 0; j < DIM; ++j) {
            new_com -> pos[j] += children[i]->new_com->pos[j] * children[j]->new_com->mass;
        }
    }

    //add each body in add_queue

}

//update body using pos/vel/mass of old
void Region::update_body(Body& old, Body& body) {
    //make an array to hold acceleration
    double acc [DIM] = {0};
    //calculate acceleration starting at the top region
    TREE_POINTER.update_acc(old, &acc);
}

//recurse through the tree
//update new_com if there are new bodies in add_queue
//then push bodies in add_queue to child regions
void Region::update_acc(Body& old, double* acc) {
    //first, switch the parity of this region's COM if necessary
    check_parity();

    //if items have been pushed to the add_queue
    //update new_com to include those, then push them down
    if(!add_queue.empty()) {
        update_com();
    }

    //if there's nothing left in this region, return
    //note: we should clean up empty regions in update()
    if(com -> mass == 0)
        return;

    //if this is a leaf region, calculate accleration and return
    if(children == nullptr) {
        if(com != nullptr) {
            add_accel(old, com, acc);
        }
    } else { //if we have children, choose to approximate or recurse
        if(check_dist(old, *this)) { //if we're far enough to approximate
            //add acceleration from this region's COM
            add_accel(old, com, acc);
        } else { //we're too close, so we need to recurse
            //update acceleration from each child region
            for(int i = 0; i < CHILDREN; ++i) {
                children[i] -> update_acc(old, acc);
            }
        }
    }
}

//split into child regions
//potential memory leak if children already contains region pointers
void Region::split() {
    //get the new half_length of the subregions
    double hl = half_length / 2;

    //create each subregion
    int pos [DIM];
    for(int i = 0; i < CHILDREN; ++i) {
        for(int j = 0; j < DIM; ++j) {
            //set each new coordinate to the offset times half side length, plus current position
            pos[j] = OFFESTS[i][j] * hl + coords[j];
        }
        //create the new region
        //note: we want the same parity so the children don't get updated yet
        //(note that bodies pushed to children have already been moved)
        //also note that we want to push bodies to new_com because bodies updated elsewhere
        //  are still in new_com in their regions
        children[i] = new Region(&pos, hl, parity);
    }
}

void Region::check_parity() {
    //switch the parity of com and add_queue if necessary
    if(parity == COUNTER % 2) {
        Body* temp = com;
        com = new_com;
        delete temp; //note: may fail silently if temp is nullptr but that's fine

        add_queue.merge(add_queue_new);
        add_queue_new = list<Body>{};

        parity = !parity;
    }
}