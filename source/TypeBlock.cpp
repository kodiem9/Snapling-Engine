#include <TypeBlock.hpp>


// PUBLIC
TypeBlock::TypeBlock(Color color, const char* text) : color(color), text(text)
{
    outline = color;
    if(outline.r >= 50) outline.r -= 50;
    else                outline.r = 0;
    if(outline.g >= 50) outline.g-= 50;
    else                outline.g = 0;
    if(outline.b >= 50) outline.b -= 50;
    else                outline.b = 0;


    id = Global::block_type_amount;
    Global::block_type_amount++;

    x = 30 + (120 * (id % 2));
    y = 30 + (50 * (id / 2));

    Global::block_colors.emplace_back(color);
}

void TypeBlock::Draw(uint16_t window_x, uint16_t window_y)
{
    if(fixed_x != window_x || fixed_y != window_y) {
        fixed_x = x + window_x;
        fixed_y = y + window_y;
    }

    if(Global::selected_block_type == id) {
        DrawRectangle(fixed_x - 20, fixed_y - 20, 110, 40, LIGHTGRAY);
    }
    DrawCircle(fixed_x, fixed_y, 12.0f, outline);
    DrawCircle(fixed_x, fixed_y, 10.0f, color);
    DrawText(text, fixed_x + 20, fixed_y - 7, 15, TEXT_COLOR);
}

void TypeBlock::Update()
{
    if(Global::MouseCollision(fixed_x - 20, fixed_y - 20, 110, 40)) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
            Global::selected_block_type = id;
        }
    }
}