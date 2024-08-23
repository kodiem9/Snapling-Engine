#include "include/Grid.hpp"

void Grid::Draw(uint16_t window_x, uint16_t window_y)
{
    DrawCircle(10 + window_x, 10 + window_y, 2, LIGHTGRAY);
}

void Grid::Update()
{
    if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
        offset_x = GetMouseX() + Global::coding_window_x;
        offset_y = GetMouseY() + Global::coding_window_y;
        held = true;
    }

    if(IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
        held = false;
    }

    if(held) {
        if(offset_x - GetMouseX() < 0)
            Global::coding_window_x = 0;
        else
            Global::coding_window_x = offset_x - GetMouseX();

        if(offset_y - GetMouseY() < 0)
            Global::coding_window_y = 0;
        else
            Global::coding_window_y = offset_y - GetMouseY();
    }
}