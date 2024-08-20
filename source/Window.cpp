#include "include/Window.hpp"

Window::Window(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t id, Type type, uint8_t scale, Color bg_color, Color outline_color)
: x(x), y(y), width(width), height(height), id(id), type(type), scale(scale), bg_color(bg_color), outline_color(outline_color)
{
    visible = true;
    holding = false;

    wheel_y = y;

    wheel_length = 0;
}

void Window::Draw(const std::function<void()>& Render)
{
    if(visible) {
        BeginScissorMode(x, y, width * scale, height * scale);

            DrawRectangle(x, y, width * scale, height * scale, bg_color);
            Render();
            DrawRectangleLinesEx(Rectangle{ (float)x, (float)y, (float)width * scale, (float)height * scale }, 3, outline_color);

        EndScissorMode();

        if(type == Type::SCROLL_WINDOW) {
            DrawRectangle(x + (width * scale) - 13, y + 3, 10, height * scale - 6, Color{ 255, 255, 255, 200 });
            DrawRectangle(x + (width * scale) - 13, wheel_y + 3, 10, 10, Color{uint8_t(outline_color.r - 40), uint8_t(outline_color.g - 40), uint8_t(outline_color.b - 40), 255});
        }
    }
}

void Window::Update()
{
    if(type == Type::SCROLL_WINDOW) {
        if(Global::MouseCollision(x, y, width * scale, height * scale)) {
            wheel_y += (int)(GetMouseWheelMove() * 5);
        }

        if(Global::MouseCollision(x + width * scale - 23, wheel_y - 7, 20, 20)) {
            if(IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) holding = true;
        }

        if(holding) {
            wheel_y = GetMouseY();
        }
        
        if(wheel_y < y) wheel_y = y;
        if(wheel_y > y + (height * scale) - 16) wheel_y = y + (height * scale) - 16;

        if(IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) holding = false;
    }
}

void Window::UpdateCursor(uint16_t old_y, uint16_t old_height)
{
    if(type == Type::SCROLL_WINDOW) {
         float multiplier = ((float)wheel_y - (float)old_y) / (float)old_height + 1.0f;
         wheel_y = ((height * scale) * multiplier) - (height * scale) + y;
    }
}