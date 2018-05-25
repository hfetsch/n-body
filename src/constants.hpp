
//define global constants here

#ifndef CONSTANTS_INCLUDED
#define CONSTANTS_INCLUDED true

//number of dimensions in the simulation
#define DIM 2

//should be 2^DIM
#define CHILDREN (1<<DIM)

long long COUNTER;

//region constraints
#define MIN_SIZE 0.001 //minimum half-length of a region

//physical constants
#define G 1 //gravitational constant

#endif