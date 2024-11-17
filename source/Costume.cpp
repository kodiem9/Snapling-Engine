#include <Costume.hpp>


// PUBLIC
Costume::Costume(uint8_t id) : x(Global::costumes_window_width / 2 - COSTUME_SIZE / 2), y(20 + (id * (COSTUME_SIZE + 20))), id(id)
{}

void Costume::Draw(uint16_t window_x, uint16_t window_y)
{
    if(fixed_x != window_x || fixed_y != window_y) {
        fixed_x = x + window_x;
        fixed_y = y + window_y;
    }

    DrawRectangle(fixed_x, fixed_y, COSTUME_SIZE, COSTUME_SIZE, (Global::selected_costumes[Global::selected_sprite] == id) ? WHITE : COSTUME_BG_COLOR);
    DrawRectangleLinesEx(Rectangle{ static_cast<float>(fixed_x), static_cast<float>(fixed_y), static_cast<float>(COSTUME_SIZE), static_cast<float>(COSTUME_SIZE) }, 3, (Global::selected_costumes[Global::selected_sprite] == id) ? COSTUME_SELECTED_OUTLINE_COLOR : COSTUME_OUTLINE_COLOR);
}

void Costume::Update() const
{
    if(Global::MouseCollision(fixed_x, fixed_y, COSTUME_SIZE, COSTUME_SIZE)) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
            Global::selected_costumes[Global::selected_sprite] = id;
        }
    }
}