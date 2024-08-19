#include "source/include/Engine.hpp"

constexpr uint16_t BUILD_NUMBER = 0;

int main()
{
    InitWindow(0, 0, TextFormat("Fetch Engine - build %i", BUILD_NUMBER));
    SetTargetFPS(60);
    Engine engine;

    while(!WindowShouldClose())
    {
        BeginDrawing();
        engine.Draw();
        ClearBackground(BLUE);
        engine.Update();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}