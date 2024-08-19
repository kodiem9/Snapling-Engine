#include "source/include/Engine.hpp"

int main()
{
    InitWindow(0, 0, "Fetch Engine - build 0");
    SetTargetFPS(60);
    Engine engine;

    while(!WindowShouldClose())
    {
        BeginDrawing();
        engine.Draw();
        ClearBackground(LIGHTGRAY);
        engine.Update();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}