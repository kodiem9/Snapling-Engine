#include "include/Costume.hpp"


// PUBLIC
Costume::Costume(uint16_t x, uint16_t y, uint16_t size) : x(x), y(y), size(size) {}

void Costume::Draw(uint16_t window_x, uint16_t window_y)
{
    DrawRectangle(x + window_x, y + window_y, size, size, COSTUME_BG_COLOR);
    DrawRectangleLinesEx(Rectangle{ (float)x + window_x, (float)y + window_y, (float)size, (float)size }, 3, COSTUME_OUTLINE_COLOR);
}

void Costume::Update()
{

}