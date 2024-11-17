#pragma once
#include "Button.hpp"

#define TEXT_COLOR Color{ 87, 94, 117, 255 }

class Category
{
    public:
        Button button;
        const char* title;

        uint16_t text_x;
        uint16_t text_y;
        
        bool visible;

        Category(const char* title, uint16_t trigger);
        void Draw();
        void Update();
};