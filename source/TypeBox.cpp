#include <TypeBox.hpp>

TypeBox::TypeBox() : selected(false), period(false), negative(false)
{}

TypeBox::~TypeBox()
{
    delete value;
}

void TypeBox::Draw(uint16_t window_x, uint16_t window_y)
{
    if(fixed_x != window_x || fixed_y != window_y) {
        fixed_x = x + window_x;
        fixed_y = y + window_y;
    }

    DrawRectangle(fixed_x, fixed_y, width, height, WHITE);
    DrawRectangleLinesEx(Rectangle{ static_cast<float>(fixed_x), static_cast<float>(fixed_y), static_cast<float>(width), static_cast<float>(height) }, 2, (selected) ? TYPEBOX_OUTLINE_COLOR_TRUE : TYPEBOX_OUTLINE_COLOR_FALSE);

    DrawText(value->c_str(), x + window_x + 5, y + window_y + 8, 15, TEXT_COLOR);
}

void TypeBox::Update()
{
    if(Global::MouseCollision(fixed_x, fixed_y, width, height)) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) { selected = true;
}
    }
    else {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) { selected = false;
}
    }
    
    if(selected) {
        key = GetCharPressed();
        if(key != 0) {
            if(MeasureText(value->c_str(), 15) + 15 < width) {
                if(type == Type::NUMBER) {
                    if(!static_cast<bool>(isdigit(key)) && key != '-') { return;
}
                    if(value->size() == 1 && value->at(0) == '0' && key != '-') {
                        value->pop_back();
                    }
                }
                if(key != '-') {
                    value->push_back(key);
                }
            }
        }

        if(type == Type::NUMBER) {
            if(key == '-') {
                negative = !negative;
                if(negative) {
                    if(value->at(0) != '0') {
                        value->insert(value->begin(), '-');
                    } else {
                        negative = false;
}
                }
                else {
                    value->erase(value->begin());
                }
            }
        }

        if(IsKeyPressed(KEY_BACKSPACE)) {
            value->pop_back();
        }

        if(type == Type::NUMBER) {
            if(value->size() == 1 && value->at(0) == '-') {
                value->pop_back();
            }

            if(value->empty()) {
                value->push_back('0');
            }
        }
    }
}