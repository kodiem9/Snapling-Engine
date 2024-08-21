#include "include/TypeBox.hpp"

TypeBox::TypeBox(uint16_t x, uint16_t y, uint16_t width, uint16_t height) : x(x), y(y), width(width), height(height) {}

void TypeBox::Draw(uint16_t window_x, uint16_t window_y)
{
    DrawRectangle(x + window_x, y + window_y, width, height, WHITE);
    DrawRectangleLinesEx(Rectangle{ (float)x + window_x, (float)y + window_y, (float)width, (float)height }, 2, WINDOW_OUTLINE_COLOR);
}

void TypeBox::Update()
{

}