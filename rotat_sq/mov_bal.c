#include "raylib.h"

int main(){
    const int W  = 1000;
    const int H = 800;
    
    InitWindow(W,H,"raylib mouse ball movemet");
    Vector2 ball = {W/2,H/2};
    Vector2 ballPosition = { -100.0f, -100.0f };

    Color ballColor = DARKBLUE;

    SetTargetFPS(60);
    
    while(!WindowShouldClose()){
        if (IsKeyDown(KEY_RIGHT))   ball.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ball.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ball.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ball.y += 2.0f;

        if (IsKeyPressed(KEY_H))
        {
            if (IsCursorHidden()) ShowCursor();
            else HideCursor();
        }
        ballPosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ballColor = MAROON;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) ballColor = LIME;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) ballColor = DARKBLUE;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) ballColor = PURPLE;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA)) ballColor = YELLOW;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_FORWARD)) ballColor = ORANGE;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_BACK)) ballColor = BEIGE;
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);
            DrawCircleV(ballPosition, 40, ballColor);
            DrawCircleV(ball, 50, MAROON);
            if (IsCursorHidden()) DrawText("CURSOR HIDDEN", 20, 60, 20, RED);
            else DrawText("CURSOR VISIBLE", 20, 60, 20, LIME);

        EndDrawing();

    }

    CloseWindow(); 

    return 0;
}