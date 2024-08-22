#include "include/PropertiesBox.hpp"

PropertiesBox::PropertiesBox()
{
    new_id = 255;

    sprite_name_box = new TypeBox(90, 20, 120, 30, TypeBox::Type::STRING);
    x_pos_box = new TypeBox(270, 20, 85, 30, TypeBox::Type::FLOAT);
    y_pos_box = new TypeBox(410, 20, 85, 30, TypeBox::Type::FLOAT);
}

PropertiesBox::~PropertiesBox()
{
    delete sprite_name_box;
    delete x_pos_box;
}

void PropertiesBox::Draw(uint16_t window_x, uint16_t window_y)
{
    if(new_id != Global::selected_sprite) {
        new_id = Global::selected_sprite;

        x_pos_string = std::to_string((int)Global::entities[new_id].x);
        y_pos_string = std::to_string((int)Global::entities[new_id].y);

        sprite_name_box->value = &Global::entities[new_id].name;
        x_pos_box->value = &x_pos_string;
        y_pos_box->value = &y_pos_string;
    }

    DrawText("Sprite", 15 + window_x, 25 + window_y, 20, TEXT_COLOR);
    sprite_name_box->Draw(window_x, window_y);

    DrawText("X", 245 + window_x, 25 + window_y, 20, TEXT_COLOR);
    x_pos_box->Draw(window_x, window_y);

    DrawText("Y", 385 + window_x, 25 + window_y, 20, TEXT_COLOR);
    y_pos_box->Draw(window_x, window_y);
}

void PropertiesBox::Update()
{
    sprite_name_box->Update();
    x_pos_box->Update();
    y_pos_box->Update();

    Global::entities[new_id].x = stoi(x_pos_string);
    Global::entities[new_id].y = stoi(y_pos_string);
}