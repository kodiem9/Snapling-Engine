#include "include/Window.hpp"

Window::Window(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t type, uint8_t scale, Color bg_color, Color outline_color)
: x(x), y(y), width(width), height(height), type(type), scale(scale), bg_color(bg_color), outline_color(outline_color)
{
    visible = true;
}

void Window::Draw(const std::function<void()>& Render)
{
    if(visible) {
        BeginScissorMode(x, y, width * scale, height * scale);

            DrawRectangle(x, y, width * scale, height * scale, bg_color);
            Render();
            DrawRectangleLinesEx(Rectangle{ (float)x, (float)y, (float)width * scale, (float)height * scale }, 3, outline_color);

        EndScissorMode();
    }
}

void Window::Update()
{

}