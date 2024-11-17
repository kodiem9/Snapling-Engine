#include <Window.hpp>

Window::Window(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t id, Type type, uint8_t scale, Color bg_color, Color outline_color, bool enabled, uint8_t category)
: x(x), y(y), wheel_y(y), width(width), height(height), wheel_length(0), id(id), type(type), scale(scale), bg_color(bg_color), outline_color(outline_color), visible(true), holding(false), enabled(enabled), category(category)
{}

void Window::Draw(const std::function<void()>& Render) const
{
    if(visible) {
        if(enabled) {
            BeginScissorMode(x, y, width * scale, height * scale);
        }

            DrawRectangle(x, y, width * scale, height * scale, bg_color);
            Render();
            DrawRectangleLinesEx(Rectangle{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(width) * scale, static_cast<float>(height) * scale }, 3, outline_color);

        if(enabled) {
            EndScissorMode();
        }

        if(type == Type::SCROLL_WINDOW) {
            if(wheel_length > 0) {
                DrawRectangle(x + (width * scale) - 13, y + 3, 10, (height * scale) - 6, Color{ 255, 255, 255, 200 });
                DrawRectangle(x + (width * scale) - 13, wheel_y + 3, 10, 10, Color{static_cast<uint8_t>(outline_color.r - 40), static_cast<uint8_t>(outline_color.g - 40), static_cast<uint8_t>(outline_color.b - 40), 255});
            }
        }
    }
}

void Window::Update()
{
    if(type == Type::SCROLL_WINDOW) {
        if(wheel_length > 0) {
            if(Global::MouseCollision(x, y, width * scale, height * scale)) {
                wheel_power += static_cast<int>(GetMouseWheelMove() * 5);
            }

            float const multiplier = static_cast<float>(height) * static_cast<float>(scale) / static_cast<float>(wheel_length);

            if(Global::MouseCollision(x + (width * scale) - 23, wheel_y - 7, 20, 20)) {
                if(IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) { holding = true;
}
            }

            if(holding) {
                wheel_y = GetMouseY();
                wheel_power = (wheel_y - y) / multiplier;
            }
            
            wheel_power = std::max<int>(wheel_power, 0);
            wheel_power = std::min<int>(wheel_power, wheel_length);

            wheel_y = y + multiplier * wheel_power;
            wheel_y = std::min<int>(wheel_y, y + (height * scale) - 16);

            if(IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) { holding = false;
}
        }
    }
}

void Window::UpdateCursor(uint16_t old_y, uint16_t old_height)
{
    if(type == Type::SCROLL_WINDOW) {
         float const multiplier = ((static_cast<float>(wheel_y) - static_cast<float>(old_y)) / static_cast<float>(old_height)) + 1.0F;
         wheel_y = ((height * scale) * multiplier) - (height * scale) + y;
    }
}