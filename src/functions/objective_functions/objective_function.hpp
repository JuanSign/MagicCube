#ifndef __OBJ_FUNC__
#define __OBJ_FUNC__

#include "../../cube/cube.hpp"

using namespace std;

class OBJECTIVE_FUNCTION
{
private:
    int option;

    int OPTION_0(CUBE cube);
    int OPTION_1(CUBE cube);
    int OPTION_2(CUBE cube);

public:
    OBJECTIVE_FUNCTION(int opt = 0);
    void SET_OPTION(int opt = 0);
    int CALCULATE(CUBE cube);
};

#endif