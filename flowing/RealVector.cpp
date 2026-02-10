#include "RealVector.hpp"
#include <cmath>

RealVector::RealVector(){}

RealVector::RealVector(float x1, float y1){
    x = x1;
    y =y1;
}

RealVector RealVector::add(RealVector &vec){
    return RealVector(x+vec.x,y+vec.y);
}

RealVector RealVector::sub(RealVector &vec){
    return RealVector(x-vec.x,y-vec.y);
}
RealVector RealVector::mul (float num){
    return RealVector(x*num,y*num);
}

RealVector RealVector::limit (float min,float max){
    float mag = getMag();
    RealVector result = *this;
    if (mag == 0)return result;

    // to reduce it to be within the limits
    if(mag>max) result = result.mul((max/mag));
    else if(mag<max) result = result.mul(min/mag);
    return result; 
    
}
float RealVector::getMag(){
    return sqrt(pow(x,2)+pow(y,2));
}

float RealVector::getangle(){
    return atan2(y,x);
}