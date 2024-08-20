#include "include/Sprite.hpp"

Sprite::Sprite(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color bg_color, Color outline_color)
: x(x), y(y), width(width), height(height), bg_color(bg_color), outline_color(outline_color) {}

void Sprite::Draw()
{
    DrawRectangle(x, y, width, height, bg_color);
    DrawRectangleLinesEx(Rectangle{ (float)x, (float)y, (float)width, (float)height }, 3, outline_color);
}

void Sprite::Update()
{

}