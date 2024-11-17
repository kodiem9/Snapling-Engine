#include <PopUp.hpp>

PopUp::PopUp(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color) : x(x), y(y), width(width), height(height), color(color)
{
    enabled = false;
    visible = true;
}

void PopUp::Draw()
{
    if(visible) {
        DrawRectangle(x, y, width, height, color);
    }
}

void PopUp::Scroll(uint16_t &modify, uint16_t value, uint16_t smoothness) { modify += (value - modify) / smoothness; }