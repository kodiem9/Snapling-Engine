#include "include/CodeBlock.hpp"


// PUBLIC
Block::Block(uint16_t x, uint16_t y, float scale, Type type, std::string text, uint16_t id, uint8_t block_type)
: x(x), y(y), scale(scale), type(type), text(text), id(id), block_type(block_type)
{
    held = false;
    remove = false;

    Data();
}

void Block::Draw(int16_t window_x, int16_t window_y)
{
    fixed_x = x + window_x;
    fixed_y = y + window_y;

    for(uint8_t i = 0; i < 3; i++) {
        switch(i)
        {
            case 0: Texture(0, 6, BLOCK_SIZE, 0, 0, 0); break;
            case 1: Texture(6, 1, BLOCK_SIZE, 6 * scale, width, 0); break;
            case 2: Texture(7, 2, BLOCK_SIZE, 7 * scale, 0, width); break;
        }

        Color color;
        if(type == Type::PLACEMENT_BLOCK)
            color = Color{ 255, 255, 255, 150 };
        else
            color = WHITE;
        
        DrawTexturePro(Global::blocks_texture, spr.source, spr.dest, spr.origin, 0.0f, color);
        DrawText(text.c_str(), fixed_x + (2 * scale + 1), fixed_y + (2 * scale + 1), 5 * (scale - 1), color);
    }
}

void Block::Update()
{
    switch(type)
    {
        case Type::NORMAL_BLOCK: {
            if(Global::MouseCollision(fixed_x, fixed_y, BLOCK_SIZE * scale + width, BLOCK_SIZE * scale)) {
                if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
                    offset_x = GetMouseX() - x;
                    offset_y = GetMouseY() - y;
                    Global::holding_block = true;
                    held = true;
                }

                if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_RIGHT) && IsKeyDown(KeyboardKey::KEY_LEFT_SHIFT)) {
                    remove = true;
                }
            }

            if(held) {
                x = GetMouseX() - offset_x;
                y = GetMouseY() - offset_y;

                if(x < 0) x = 0;
                if(x > (Global::coding_window_width - BLOCK_SIZE * scale) + Global::block_grid[Global::selected_sprite].x) x = (Global::coding_window_width - BLOCK_SIZE * scale) + Global::block_grid[Global::selected_sprite].x;
                if(y < 0) y = 0;
                if(y > (GetScreenHeight() - 140 - BLOCK_SIZE * scale) + Global::block_grid[Global::selected_sprite].y) y = (GetScreenHeight() - 140 - BLOCK_SIZE * scale) + Global::block_grid[Global::selected_sprite].y;
            }


            if(IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT) && held) {
                held = false;
                Global::holding_block = false;
            }
        }
        break;

        case Type::PANEL_BLOCK: {
            if(Global::MouseCollision(fixed_x, fixed_y, BLOCK_SIZE * scale + width, BLOCK_SIZE * scale)) {
                if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
                    Global::selected_panel_block = id;
                    Global::holding_block = true;
                }
            }
        }
        break;

        case Type::PLACEMENT_BLOCK: {
            if(Global::selected_panel_block > 0) {
                x = GetMouseX() - offset_x;
                y = GetMouseY() - offset_y;
            }

            if(IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT) && Global::selected_panel_block > 0) {
                if(x > Global::coding_panels_width) {
                    Global::execute_new_block = true;
                    Global::holding_block = false;
                }
                Global::selected_panel_block = 0;
            }
        }
        break;

        default: break;
    }
}

void Block::Data()
{
    width = MeasureText(text.c_str(), 5 * (scale - 1));
}


// PRIVATE
void Block::Texture(float _x, float _width, float _height, float _offset_x, float _offset_width, float _offset_width_x)
{
    spr.source = Rectangle{ _x, 0, _width, _height };
    spr.dest = Rectangle{ (float)fixed_x + _offset_x + _offset_width_x, (float)fixed_y, _width * scale + _offset_width, _height * scale };
}