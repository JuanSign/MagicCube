#include "hcsa.hpp"

#include <climits>
#include <iostream>

using namespace std;

HCSA::HCSA(CUBE cube, int opt)
{
    this->cube = cube;
    this->obj_func = OBJECTIVE_FUNCTION(opt);
}

void HCSA::SET_CUBE(CUBE cube) { this->cube = cube; }
void HCSA::SET_OPTION(int opt) { this->obj_func.SET_OPTION(opt); }

pair<int, int> HCSA::FIND_BEST()
{
    pair<int, int> res;
    int best = INT_MAX;
    for (int i = 1; i <= 124; i++)
    {
        for (int j = i + 1; j <= 125; j++)
        {
            this->cube.SWAP(i, j);
            int cur = this->obj_func.CALCULATE(this->cube);
            if (cur < best)
            {
                best = cur;
                res = {i, j};
            }
            this->cube.SWAP(i, j);
        }
    }
    return res;
}

void HCSA::RUN(bool output)
{
    int iteration = 1;
    while (true)
    {
        pair<int, int> bestSwap = this->FIND_BEST();

        int curScore = this->obj_func.CALCULATE(this->cube);
        if (output)
        {
            cout << "-----" << endl;
            cout << "iteration-" << iteration++ << endl;
            cout << "CURRENT SCORE: " << curScore << endl;
        }

        this->cube.SWAP(bestSwap.first, bestSwap.second);
        if (output)
            cout << "SWAP: " << bestSwap.first << " " << bestSwap.second << endl;
        int newScore = this->obj_func.CALCULATE(this->cube);
        if (output)
        {
            cout << "NEW SCORE: " << newScore << endl;
            cout << "-----" << endl;
        }

        if (newScore >= curScore)
        {
            this->cube.SWAP(bestSwap.first, bestSwap.second);
            return;
        }
    }
}
