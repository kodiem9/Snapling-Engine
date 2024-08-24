#include "include/Category.hpp"


// PUBLIC
Category::Category(const char* title, uint16_t trigger)
{
    button.x = 10 + (Global::category_button_texture.width * 4 * Global::category_amount);
    button.y = 8;
    button.trigger = trigger;
    button.type = Button::Type::CHECKBOX;
    button.frame = 0;
    button.scale = 4.0f;
    button.texture = &Global::category_button_texture;
    button.checkbox = &Global::current_category;
    button.value = Global::category_amount;
    this->title = title;

    text_x = button.x + (Global::category_button_texture.width * button.scale) / 2 - MeasureText(title, 15) / 2;
    text_y = (Global::category_button_texture.height * button.scale) / 2;

    visible = true;

    Global::category_amount++;
}

void Category::Draw()
{
    if(visible) {
        button.Draw();
        DrawText(title, text_x, (Global::current_category == button.value) ? text_y : text_y + 8, 15, (Global::current_category == button.value) ? Color{ 177, 62, 83, 255 } : TEXT_COLOR);
    }
}

void Category::Update()
{
    if(visible) {
        button.Update();
    }
}