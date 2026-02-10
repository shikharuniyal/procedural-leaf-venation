#include "raylib.h"
#include "config.hpp"
#include <iostream>
#include"particle.hpp"

#include<cmath>
#include<time.h>
#include <unistd.h>


int main(){


    vector<particle> particles;

    for(int i = 0;i<num_par;i++){
        particle p(
            RealVector((float)(rand() % W),(float)(rand() % H)),
            RealVector(0,0),
            Par_min_s,
            Par_max_s
        );
        particles.push_back(p);

    }
    InitWindow(W,H,"lets flow");
    //srand(time(nullptr));
    SetTargetFPS(120);

    double MULT = 0.5f;
    double len = SCL*MULT;

    //creating the grid with the slots with the start_pt at the center of the slot
    for(int y = 0;y<Rows; y++){
        for(int x = 0;x<Cols; x++){
            slot s;
            s.start_pt = {(float) SCL*x +SCL /2,(float)SCL*y +SCL /2};
            BOARD[y][x] = s;
        }
    }
    double f = 0.01;
    double fact =  0;
    while (!WindowShouldClose()){
        BeginDrawing();
        //ClearBackground(BLACK);


        if (IsKeyPressed(KEY_H))
        {
            if (IsCursorHidden()) ShowCursor();
            else HideCursor();
        }

        Vector2 cur_pos = GetMousePosition();

        //double fact = field_func((double)cur_pos.x,(double)cur_pos.y);
        
        fact  = (fact+0.1f) -3.414f * floor((fact+0.1f)/ 3.414f);
        
        
        usleep(5000);
        
        for(int  y = 0;y<Rows;y++){
            for(int x = 0;x<Cols; x++){

                double angle = field_func((double)x*0.03+f,(double)y*0.03+f);
                //angle += f;
                BOARD[y][x].vec = RealVector(cos(angle)*len,sin(angle)*len);

                Vector2 end  = {
                    BOARD[y][x].start_pt.x+BOARD[y][x].vec.x ,
                    BOARD[y][x].start_pt.y+BOARD[y][x].vec.y
                };

                //DrawLineEx(BOARD[y][x].start_pt,end,2,BLACK);
            }

        }

        //simulating and drawiing the particles
        for(int i =0;i<num_par;i++){
            RealVector mv = BOARD[(int)particles[i].pos.y /SCL][(int)particles[i].pos.x / SCL].vec;
            particles[i].applyForce(mv);
            particles[i].update();
            particles[i].show();
        }

        //updates
        //f +=0.01;

        EndDrawing();
    }
    return 0;
}