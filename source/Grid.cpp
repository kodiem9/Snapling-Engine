#include "include/Grid.hpp"


// PUBLIC
Grid::Grid()
{
    Data();
}

void Grid::Draw(uint16_t window_x, uint16_t window_y)
{
    for(Dot &dot: dots) {
        DrawCircle(dot.x + window_x - Global::block_grid[Global::selected_sprite].x, dot.y + window_y - Global::block_grid[Global::selected_sprite].y, 2, LIGHTGRAY);
    }
}

void Grid::Update()
{
    if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
        offset_x = GetMouseX() + Global::block_grid[Global::selected_sprite].x;
        offset_y = GetMouseY() + Global::block_grid[Global::selected_sprite].y;
        held = true;
    }

    if(IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT) && held) {
        held = false;
    }

    if(held) {
        if(Global::MouseCollision(Global::coding_window_x, 40, Global::coding_window_width, GetScreenHeight() - 140) && !Global::holding_block) {
            if(offset_x - GetMouseX() < 0)
                Global::block_grid[Global::selected_sprite].x = 0;
            else
                Global::block_grid[Global::selected_sprite].x = offset_x - GetMouseX();

            if(offset_y - GetMouseY() < 0)
                Global::block_grid[Global::selected_sprite].y = 0;
            else
                Global::block_grid[Global::selected_sprite].y = offset_y - GetMouseY();
        }
    }

    for(Dot &dot: dots) {
        if(dot.x - Global::block_grid[Global::selected_sprite].x < 0) {
            dot.x += move_x;
        }
        if(dot.x - Global::block_grid[Global::selected_sprite].x > move_x) {
            dot.x -= move_x;
        }
        if(dot.y - Global::block_grid[Global::selected_sprite].y < 0) {
            dot.y += move_y;
        }
        if(dot.y - Global::block_grid[Global::selected_sprite].y > move_y) {
            dot.y -= move_y;
        }
    }
}

void Grid::Data()
{
    uint16_t x;
    uint16_t y;

    for(x = 0; x < (Global::coding_window_width / GRID_GAPS) + 1; x++) {
        for(y = 0; y < ((GetScreenHeight() - 140) / GRID_GAPS) + 1; y++) {
            dots.emplace_back(x * 60 + 10, y * 60 + 10);
        }
    }

    move_x = x * GRID_GAPS;
    move_y = y * GRID_GAPS;
}