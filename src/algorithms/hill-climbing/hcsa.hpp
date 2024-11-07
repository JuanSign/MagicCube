#ifndef __HCSA__
#define __HCSA__

#include "../../cube/cube.hpp"
#include "../../functions/objective_functions/objective_function.hpp"

#include <vector>

class HCSA
{
private:
    CUBE cube;
    OBJECTIVE_FUNCTION obj_func;
    vector<double> AVG_DIF;
    vector<double> TIME;
    vector<int> OBJ_SCORE;

    pair<int, int> FIND_BEST();

public:
    HCSA(CUBE cube, int opt = 0);

    void SET_CUBE(CUBE cube);
    void SET_OPTION(int opt = 0);
    void RUN(bool output = false);
};

#endif