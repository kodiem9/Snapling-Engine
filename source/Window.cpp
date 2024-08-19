#include "include/Window.hpp"

Window::Window(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t type, uint8_t scale) : x(x), y(y), width(width), height(height), type(type), scale(scale) {}

void Window::Draw(const std::function<void()>& Render)
{
    BeginScissorMode(x, y, width * scale, height * scale);

        DrawRectangle(x, y, width * scale, height * scale, WHITE);
        Render();
        DrawRectangleLinesEx(Rectangle{ (float)x, (float)y, (float)width * scale, (float)height * scale }, 3, WINDOW_OUTLINE_COLOR);

    EndScissorMode();
}

void Window::Update()
{

}