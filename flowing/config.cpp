#include "config.hpp"
#include <cmath>
#include <algorithm>
using std::clamp;

vector<vector<slot>> BOARD(Rows+1, vector<slot>(Cols+1));\


double map_to(double minimum, double maximum, double new_min, double new_max,double value){
    value = clamp(value,minimum,maximum);
    return (value - minimum)*(new_max-new_min)/ (maximum-minimum)  + new_min;
}

double field_func(double x, double y){
    return RealVector(cos(y),sin(x)).getangle();
}