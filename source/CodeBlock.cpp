#include "include/CodeBlock.hpp"


// PUBLIC
Block::Block(uint16_t x, uint16_t y, float scale, Type type) : x(x), y(y), scale(scale), type(type) {}

void Block::Draw(uint16_t window_x, uint16_t window_y)
{
    fixed_x = x + window_x;
    fixed_y = y + window_y;

    for(uint8_t i = 0; i < 3; i++) {
        switch(i)
        {
            case 0: Texture(0, 6, BLOCK_SIZE, 0); break;
            case 1: Texture(6, 1, BLOCK_SIZE, 6 * scale); break;
            case 2: Texture(7, 2, BLOCK_SIZE, 7 * scale); break;
        }
        DrawTexturePro(Global::blocks_texture, spr.source, spr.dest, spr.origin, 0.0f, WHITE);
    }
}

void Block::Update()
{
    switch(type)
    {
        case Type::NORMAL_BLOCK: {
            if(Global::MouseCollision(fixed_x, fixed_y, BLOCK_SIZE * scale, BLOCK_SIZE * scale)) {
                if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
                    offset_x = GetMouseX() - x;
                    offset_y = GetMouseY() - y;
                    held = true;
                }
            }

            if(held) {
                x = GetMouseX() - offset_x;
                y = GetMouseY() - offset_y;
            }

            if(x < 0) x = 0;
            if(x > (Global::coding_window_width - BLOCK_SIZE * scale)) x = (Global::coding_window_width - BLOCK_SIZE * scale);
            if(y < 0) y = 0;
            if(y > (GetScreenHeight() - 140 - BLOCK_SIZE * scale)) y = (GetScreenHeight() - 140 - BLOCK_SIZE * scale);

            if(IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
                held = false;
            }
        }
        break;

        default: break;
    }
}


// PRIVATE
void Block::Texture(float _x, float _width, float _height, float _offset_x)
{
    spr.source = Rectangle{ _x, 0, _width, _height };
    spr.dest = Rectangle{ (float)fixed_x + _offset_x, (float)fixed_y, _width * scale, _height * scale };
}