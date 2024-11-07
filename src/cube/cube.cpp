#include "cube.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

void CUBE::GENERATE_POSITIONS()
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
                this->POSITIONS[this->DATA[i][j][k] - 1] = {i, j, k};
}

void CUBE::GENERATE_CONSTRAINTS()
{
    /*
        CONSTRAINTS [0]-[3]     : space diagonals (4)
        CONSTRAINTS [4]-[33]     : plane diagonals (30)
        CONSTRAINTS [34] - [58]  : rows            (25)
        CONTRAINTS [59] - [83]   : columns         (25)
        CONSTRAINTS [84] - [108] : pillars         (25)
    */
    vector<vector<int>> constraints;

    // space diagonals
    vector<int> sd[4];
    for (int i = 0; i < 5; i++)
    {
        sd[0].push_back(this->DATA[i][i][i]);
        sd[1].push_back(this->DATA[i][i][4 - i]);
        sd[2].push_back(this->DATA[i][4 - i][i]);
        sd[3].push_back(this->DATA[i][4 - i][4 - i]);
    }
    for (int i = 0; i < 4; i++)
        constraints.push_back(sd[i]);

    // plane diagonals
    vector<vector<int>> pd;
    // bottom to top
    for (int i = 0; i < 5; i++)
    {
        vector<int> cur_pd[2];
        for (int c = 0; c < 5; c++)
        {
            cur_pd[0].push_back(this->DATA[i][c][c]);
            cur_pd[1].push_back(this->DATA[i][c][4 - c]);
        }
        pd.push_back(cur_pd[0]);
        pd.push_back(cur_pd[1]);
    }
    // front to back
    for (int j = 0; j < 5; j++)
    {
        vector<int> cur_pd[2];
        for (int c = 0; c < 5; c++)
        {
            cur_pd[0].push_back(this->DATA[c][j][c]);
            cur_pd[1].push_back(this->DATA[c][j][4 - c]);
        }
        pd.push_back(cur_pd[0]);
        pd.push_back(cur_pd[1]);
    }
    // left to right
    for (int k = 0; k < 5; k++)
    {
        vector<int> cur_pd[2];
        for (int c = 0; c < 5; c++)
        {
            cur_pd[0].push_back(this->DATA[c][c][k]);
            cur_pd[1].push_back(this->DATA[c][4 - c][k]);
        }
        pd.push_back(cur_pd[0]);
        pd.push_back(cur_pd[1]);
    }
    for (int i = 0; i < 30; i++)
        constraints.push_back(pd[i]);

    // rows, columns, and pillars
    vector<int> rows[25], columns[25], pillars[25];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                rows[5 * i + j].push_back(this->DATA[i][j][k]);
                columns[5 * i + k].push_back(this->DATA[i][j][k]);
                pillars[5 * j + k].push_back(this->DATA[i][j][k]);
            }
        }
    }
    for (int i = 0; i < 25; i++)
        constraints.push_back(rows[i]);
    for (int i = 0; i < 25; i++)
        constraints.push_back(columns[i]);
    for (int i = 0; i < 25; i++)
        constraints.push_back(pillars[i]);

    // add all constraints to this->CONSTRAINTS
    for (int i = 0; i < 109; i++)
        for (int j = 0; j < 5; j++)
            this->CONSTRAINTS[i][j] = constraints[i][j];

    // update the constraint graph
    for (int i = 0; i < 109; i++)
        for (int j = 0; j < 5; j++)
            this->ADJ[this->CONSTRAINTS[i][j] - 1].push_back(i);
}

CUBE::CUBE(int seed)
{
    // initiate the vector of number [1,125]
    vector<int> numbers(125);
    iota(numbers.begin(), numbers.end(), 1);

    // randomly shuffle the vector
    random_device rd;
    // Mersenne Twister random number generator
    mt19937 mt;
    if (seed)
        mt.seed(seed);
    else
        mt.seed(rd());
    shuffle(numbers.begin(), numbers.end(), mt);

    // assign the numbers to the cube
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
                this->DATA[i][j][k] = numbers[25 * i + 5 * j + k];

    // calculate position for each number
    this->GENERATE_POSITIONS();
    // generate magic cube's constraints
    this->GENERATE_CONSTRAINTS();
}

void CUBE::SWAP(int i, int j)
{
    array<int, 3> i_cord = this->POSITIONS[i - 1]; // coordinate of number i
    array<int, 3> j_cord = this->POSITIONS[j - 1]; // coordinate of number j

    // update CONSTRAINTS
    for (int c = 0; c < 109; c++)
    {
        for (int &e : this->CONSTRAINTS[c])
        {
            if (e == i)
                e = j;
            else if (e == j)
                e = i;
        }
    }

    // swap
    swap(this->DATA[i_cord[0]][i_cord[1]][i_cord[2]], this->DATA[j_cord[0]][j_cord[1]][j_cord[2]]);
    swap(this->ADJ[i - 1], this->ADJ[j - 1]);
    swap(this->POSITIONS[i - 1], this->POSITIONS[j - 1]);
}

void CUBE::PRINT_CUBE()
{
    cout << "---PRINTING CUBE---" << endl;
    for (int i = 4; i >= 0; i--)
    {
        cout << "LAYER " << i + 1 << endl;
        for (int j = 4; j >= 0; j--)
        {
            cout << "ROW " << j + 1 << ": ";
            for (int k = 0; k < 5; k++)
            {
                cout << this->DATA[i][j][k] << " ";
            }
            cout << endl;
        }
    }
    cout << "------" << endl;
}

void CUBE::PRINT_CONSTRAINS()
{
    /*
    CONSTRAINTS [0]-[3]     : space diagonals (4)
    CONSTRAINTS [4]-[33]     : plane diagonals (30)
    CONSTRAINTS [34] - [58]  : rows            (25)
    CONTRAINTS [59] - [83]   : columns         (25)
    CONSTRAINTS [84] - [108] : pillars         (25)
    */
    cout << "---PRINTING CUBE'S CONSTRAINTS---" << endl;
    for (int i = 0; i < 109; i++)
    {
        if (i < 4)
            cout << "SPACE DIAGONALS: ";
        else if (i < 34)
            cout << "PLANE DIAGONALS: ";
        else if (i < 59)
            cout << "ROWS: ";
        else if (i < 84)
            cout << "COLUMNS: ";
        else
            cout << "PILLARS: ";

        for (int x = 0; x < 5; x++)
            cout << this->CONSTRAINTS[i][x] << " ";
        cout << endl;
    }
    cout << "------" << endl;
}