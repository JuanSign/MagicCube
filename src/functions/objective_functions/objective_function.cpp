#include "objective_function.hpp"

#include <numeric>

using namespace std;

int OBJECTIVE_FUNCTION::OPTION_0()
{
    int res = 0;
    for (int i = 0; i < 109; i++)
        res += abs(315 - accumulate(this->cube.CONSTRAINTS[i].begin(),
                                    this->cube.CONSTRAINTS[i].end(),
                                    0));
    return res;
}

int OBJECTIVE_FUNCTION::OPTION_1()
{
    int res = 0;
    for (int i = 0; i < 109; i++)
    {
        int curRes = abs(315 - accumulate(this->cube.CONSTRAINTS[i].begin(),
                                          this->cube.CONSTRAINTS[i].end(),
                                          0));
        int relatedConstraint = 0;
        for (int c : this->cube.CONSTRAINTS[i])
        {
            relatedConstraint += (this->cube.ADJ[c - 1].size() - 1);
        }
        curRes *= (relatedConstraint - 1);
        res += curRes;
    }
    return res;
}

int OBJECTIVE_FUNCTION::OPTION_2()
{
    int res = 0;
    for (int i = 0; i < 109; i++)
    {
        int curNeed = (315 - accumulate(this->cube.CONSTRAINTS[i].begin(),
                                        this->cube.CONSTRAINTS[i].end(),
                                        0));
        int curRes = abs(curNeed);
        int mult = 0;
        for (int el : this->cube.CONSTRAINTS[i])
        {
            for (int rel : this->cube.ADJ[el - 1])
            {
                if (rel == i)
                    continue;
                int oldDif = accumulate(this->cube.CONSTRAINTS[rel].begin(),
                                        this->cube.CONSTRAINTS[rel].end(),
                                        0);
                int newDif = oldDif + curNeed;
                oldDif = abs(oldDif);
                newDif = abs(newDif);
                mult += oldDif - newDif;
            }
        }
        mult = max(mult, 1);
        curRes *= mult;
        res += curRes;
    }
    return res;
}

OBJECTIVE_FUNCTION::OBJECTIVE_FUNCTION(CUBE c, int opt)
{
    this->cube = c;
    this->option = opt;
}

void OBJECTIVE_FUNCTION::SET_CUBE(CUBE c) { this->cube = c; }
void OBJECTIVE_FUNCTION::SET_OPTION(int opt) { this->option = opt; }

int OBJECTIVE_FUNCTION::CALCULATE()
{
    if (this->option == 1)
        return OPTION_1();
    else if (this->option == 2)
        return OPTION_2();
    else
        return OPTION_0();
}
