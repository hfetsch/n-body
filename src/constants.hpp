
//define global constants here

#ifndef CONSTANTS_INCLUDED
#define CONSTANTS_INCLUDED true

//number of dimensions in the simulation
#define DIM 2

//should be 2^DIM
#define CHILDREN (1<<DIM)

//array of offsets for subregions
int OFFSETS [CHILDREN][DIM];

long long COUNTER;

//region constraints
#define MIN_SIZE 0.001 //minimum half-length of a region

//physical constants
#define G 1 //gravitational constant


//initialization functions
void init() {
    //create offsets
    //assign coordinates of subregions using binary representations
    for(int i = 0; i < CHILDREN; ++i) {
        for(int j = 0; j < DIM; ++j) {
            int n = i & (1 << j); //select just the bit we care about

            //set the offset to 1 or -1
            if(n == 0)
                OFFSETS[i][j] = -1;
            else
                OFFSETS[i][j] = 1;
        }
    }
}

#endif