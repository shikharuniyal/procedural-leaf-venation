#pragma once

class RealVector{
    public:
        float x,y;

        RealVector();
        RealVector(float x,float y);

        RealVector add (RealVector &vec);
        RealVector sub (RealVector &vec);
        RealVector mul (float num);
        RealVector limit (float min,float max); //speed control of the vector effect on the object
        float getMag();
        float getangle();

};