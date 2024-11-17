#include <Engine.hpp>

#define BACKGROUND_COLOR Color{ 229, 240, 255, 255 }
constexpr uint16_t BUILD_NUMBER = 1636;

auto main() -> int
{
    InitWindow(0, 0, TextFormat("Snapling - build %i", BUILD_NUMBER));
    SetTargetFPS(60);
    Engine engine;

    while(!WindowShouldClose())
    {
        BeginDrawing();
        engine.Update();
        ClearBackground(BACKGROUND_COLOR);
        engine.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}