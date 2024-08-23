#include "include/BlockTypePanel.hpp"


// PUBLIC
void BlockTypePanel::Draw(uint16_t window_x, uint16_t window_y)
{
    DrawRectangle(x + window_x, y + window_y, 50, 50, RED);
}

void BlockTypePanel::Update()
{

}