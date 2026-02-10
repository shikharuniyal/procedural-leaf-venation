#include "raylib.h"
#include <unistd.h>
#define w 800
#define h 450
int main(void)
{
    InitWindow(800, 450, "raylib rotating square");
    int i = 0;
    SetTargetFPS(60);

    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f }; // Where the camera is
    camera.target   = (Vector3){ 0.0f, 0.0f, 0.0f }; // What it looks at
    camera.up       = (Vector3){ 0.0f, 1.0f, 0.0f }; // "Up" direction
    camera.fovy     = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Rectangle rec ={(w/2)-10 +i,(h/2)-10,100,100};
    Rectangle rec2 = rec;
    Vector2 ori = {50,50};
    float rot = 0;

    while (!WindowShouldClose())
    {
        usleep(10000);
        BeginDrawing();
        DrawFPS(20,20);
        DrawText("ACCHA LAVDE", 69,69,20,WHITE);
            ClearBackground(BLANK);
            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            if(i<w-450 ){

                
                rec2.x = (w/2)-10  -50;
                rec2.y = rec.y -50;
                DrawRectangleRec(rec2,BLUE);
                rec.x  = (w/2)-10 +i;
                DrawRectanglePro(rec ,  ori  ,rot+i,PURPLE);
            }
            
            if(i>w-450){
                BeginMode3D(camera);
                DrawCircle3D((Vector3){0,0,0}, 2.0f, (Vector3){0,1,0}, 0.0f, #FF5733 );
                EndMode3D();

            }
            

        EndDrawing();
        i = i+1;
    }

    CloseWindow();

    return 0;
}