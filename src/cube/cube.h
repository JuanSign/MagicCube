#ifndef __CUBE__
#define __CUBE__

#include <array>
#include <vector>

using namespace std;

class CUBE
{
private:
    array<array<array<int, 5>, 5>, 5> DATA; // literal cube
    array<array<int, 3>, 125> POSITIONS;    // the (i,j,k)-coordinate of each number
    array<array<int, 5>, 109> CONSTRAINTS;  // the 109 magic cube's constraints
    array<vector<int>, 125> ADJ;            // the adjacency list of the constraint graph

    void GENERATE_POSITIONS();   // calculate the positions of each number
    void GENERATE_CONSTRAINTS(); // generate the magic cube's contraints

public:
    CUBE(int seed = 0);      // instantiate a random cube (0 or no seed for true random, seed != 0 for pseudo-random)
    void SWAP(int i, int j); // swap number i with number j
    void PRINT_CUBE();       // output the cube to stdout
    void PRINT_CONSTRAINS(); // output the constraint list to stdout
};

#endif