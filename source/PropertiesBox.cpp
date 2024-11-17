#include <PropertiesBox.hpp>


// PUBLIC
PropertiesBox::PropertiesBox() : new_id(255), sprite_name_box(new TypeBox), x_pos_box(new TypeBox), y_pos_box(new TypeBox)
{
    Reset(1);
}

PropertiesBox::~PropertiesBox()
{ 
    delete sprite_name_box;
    delete x_pos_box;
    delete y_pos_box;
}

void PropertiesBox::Draw(uint16_t window_x, uint16_t window_y)
{
    if(new_id != Global::selected_sprite) {
        new_id = Global::selected_sprite;

        x_pos_string = std::to_string(Global::entities[new_id].x);
        y_pos_string = std::to_string(Global::entities[new_id].y);

        sprite_name_box->value = &Global::entities[new_id].name;
        x_pos_box->value = &x_pos_string;
        y_pos_box->value = &y_pos_string;
    }

    DrawText("Sprite", sprite_name_text_offset.x + window_x, sprite_name_text_offset.y + window_y, 20, TEXT_COLOR);
    sprite_name_box->Draw(window_x, window_y);

    DrawText("X", x_pos_text_offset.x + window_x, x_pos_text_offset.y + window_y, 20, TEXT_COLOR);
    x_pos_box->Draw(window_x, window_y);

    DrawText("Y", y_pos_text_offset.x + window_x, y_pos_text_offset.y + window_y, 20, TEXT_COLOR);
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

void PropertiesBox::Reset(uint8_t mode)
{
    if(mode != 0u) {
        Data(sprite_name_box, 90, 20, 120, 30, TypeBox::Type::STRING);
        sprite_name_text_offset.x = 15;
        sprite_name_text_offset.y = 25;

        Data(x_pos_box, 270, 20, 85, 30, TypeBox::Type::NUMBER);
        x_pos_text_offset.x = 245;
        x_pos_text_offset.y = 25;

        Data(y_pos_box, 410, 20, 85, 30, TypeBox::Type::NUMBER);
        y_pos_text_offset.x = 385;
        y_pos_text_offset.y = 25;
    }
    else {
        Data(sprite_name_box, 120, 5, 120, 30, TypeBox::Type::STRING);
        sprite_name_text_offset.x = 50;
        sprite_name_text_offset.y = 10;

        Data(x_pos_box, 50, 40, 85, 30, TypeBox::Type::NUMBER);
        x_pos_text_offset.x = 30;
        x_pos_text_offset.y = 45;

        Data(y_pos_box, 170, 40, 85, 30, TypeBox::Type::NUMBER);
        y_pos_text_offset.x = 150;
        y_pos_text_offset.y = 45;
    }
}


// PRIVATE
void PropertiesBox::Data(TypeBox *type_box, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TypeBox::Type type)
{
    type_box->x = x;
    type_box->y = y;
    type_box->width = width;
    type_box->height = height;
    type_box->type = type;
}