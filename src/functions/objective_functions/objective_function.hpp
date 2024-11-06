#ifndef __OBJ_FUNC__
#define __OBJ_FUNC__

#include "../../cube/cube.hpp"

using namespace std;

class OBJECTIVE_FUNCTION
{
private:
    CUBE cube;
    int option;

    int OPTION_0();
    int OPTION_1();
    int OPTION_2();

public:
    OBJECTIVE_FUNCTION(CUBE c, int opt = 0);
    void SET_CUBE(CUBE c);
    void SET_OPTION(int opt = 0);
    int CALCULATE();
};

#endif