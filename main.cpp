#include "raylib.h"
#include <vector>
#include <cmath>

struct DataPoint {
    float x, y;
};

std::vector<DataPoint> generateData(int numPoints) {
    std::vector<DataPoint> data;
    for (int i = 0; i < numPoints; i++) {
        float x = static_cast<float>(i) / numPoints;
        float y = std::sin(x * 6.28f * 3.0f);
        data.push_back({x, y});
    }
    return data;
}

Vector2 dataToScreen(float x, float y, int width, int height, int margin) {
    float yMin = -1.5f, yMax = 1.5f;
    int plotW = width - 2 * margin;
    int plotH = height - 2 * margin;
    return {
        margin + x * plotW,
        margin + plotH - ((y - yMin) / (yMax - yMin)) * plotH
    };
}

int main() {
    const int WIDTH = 1200, HEIGHT = 800, MARGIN = 60;
    
    InitWindow(WIDTH, HEIGHT, "Raylib Visualization");
    SetTargetFPS(240);

    auto data = generateData(200);

    while (!WindowShouldClose()) {
        // Update data animation
        float time = GetTime();
        for (size_t i = 0; i < data.size(); i++) {
            data[i].y = std::sin(data[i].x * 6.28f * 3.0f + time);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw axes
        DrawLineEx({MARGIN, MARGIN}, {MARGIN, HEIGHT - MARGIN}, 2, WHITE);
        DrawLineEx({MARGIN, HEIGHT - MARGIN}, {WIDTH - MARGIN, HEIGHT - MARGIN}, 2, WHITE);
        

        // Draw data
        for (size_t i = 1; i < data.size(); i++) {
            Vector2 p1 = dataToScreen(data[i-1].x, data[i-1].y, WIDTH, HEIGHT, MARGIN);
            Vector2 p2 = dataToScreen(data[i].x, data[i].y, WIDTH, HEIGHT, MARGIN);
            DrawLineEx(p1, p2, 2, BLUE);
            DrawCircleV(p2, 3, SKYBLUE);
        }

        DrawText("Data Visualization", 10, 10, 20, WHITE);
        DrawFPS(WIDTH - 100, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
