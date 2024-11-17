#include <CodeBlock.hpp>


// PUBLIC
Block::Block(uint16_t x, uint16_t y, float scale, Type type, std::string text, uint16_t id, uint8_t block_type)
: x(x), y(y), scale(scale), type(type), text(std::move(std::move(text))), id(id), block_type(block_type), held(false), remove(false)
{
    Data();
}

void Block::Draw(int16_t window_x, int16_t window_y)
{
    fixed_x = x + window_x;
    fixed_y = y + window_y;

    for(uint8_t i = 0; i < 3; i++) {
        switch(i)
        {
            case 0: Texture(0, 6, Global::blocks_texture.width, 0, 0, 0); break;
            case 1: Texture(6, 1, Global::blocks_texture.width, 6 * scale, width, 0); break;
            case 2: Texture(7, 2, Global::blocks_texture.width, 7 * scale, 0, width); break;
        }

        Color texture_color;
        Color text_color;
        if(type == Type::PLACEMENT_BLOCK) {
            texture_color = color;
            texture_color.a -= 100;
            text_color = WHITE;
            text_color.a -= 100;
        }
        else {
            texture_color = color;
            text_color = WHITE;
        }
        
        DrawTexturePro(Global::blocks_texture.texture, spr.source, spr.dest, spr.origin, 0.0F, texture_color);
        DrawText(text.c_str(), fixed_x + (2 * scale + 1), fixed_y + (2 * scale + 1), 5 * (scale - 1), text_color);
    }
}

void Block::Update()
{
    switch(type)
    {
        case Type::NORMAL_BLOCK: {
            if(Global::MouseCollision(fixed_x, fixed_y, (Global::blocks_texture.width * scale) + width, Global::blocks_texture.height * scale)) {
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

                x = std::max<int>(x, 0);
                if(x > (Global::coding_window_width - Global::blocks_texture.width * scale) + Global::block_grid_position[Global::selected_sprite].x) { x = (Global::coding_window_width - Global::blocks_texture.height * scale) + Global::block_grid_position[Global::selected_sprite].x;
}
                y = std::max<int>(y, 0);
                if(y > (GetScreenHeight() - 140 - Global::blocks_texture.width * scale) + Global::block_grid_position[Global::selected_sprite].y) { y = (GetScreenHeight() - 140 - Global::blocks_texture.height * scale) + Global::block_grid_position[Global::selected_sprite].y;
}
            }


            if(IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT) && held) {
                held = false;
                Global::holding_block = false;
            }
        }
        break;

        case Type::PANEL_BLOCK: {
            if(Global::MouseCollision(fixed_x, fixed_y, (Global::blocks_texture.width * scale) + width, Global::blocks_texture.height * scale)) {
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
    color = Global::block_colors[block_type];
}


// PRIVATE
void Block::Texture(float _x, float _width, float _height, float _offset_x, float _offset_width, float _offset_width_x)
{
    spr.source = Rectangle{ _x, 0, _width, _height };
    spr.dest = Rectangle{ static_cast<float>(fixed_x) + _offset_x + _offset_width_x, static_cast<float>(fixed_y), (_width * scale) + _offset_width, _height * scale };
}