#include "raylib.h"
#include <vector>
#include "RealVector.hpp"

using std::vector;
#define W  800
#define H  800
#define  SCL 10
#define Rows (float)(W/SCL)
#define Cols (float)(H/SCL)

//particle variables
#define Par_rad 1
#define Par_max_s 2
#define Par_min_s 1
#define num_par 100

//each slot in the grid
struct slot{
    RealVector vec;
    Vector2 start_pt;
};

extern vector<vector<slot>> BOARD;

double map_to(double minimum, double maximum, double new_min, double new_max,double value);
double field_func(double x, double y);