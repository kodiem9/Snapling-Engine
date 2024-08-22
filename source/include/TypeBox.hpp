#pragma once
#include "Global.hpp"

#define TYPEBOX_OUTLINE_COLOR_FALSE     Color{ 195, 204, 217, 255 }
#define TYPEBOX_OUTLINE_COLOR_TRUE      Color{ 177, 62, 83, 255 }
#define TEXT_COLOR                      Color{ 87, 94, 117, 255 }


class TypeBox
{
    public:
        enum class Type
        {
            STRING,
            FLOAT
        };

        std::string *value;
        
        Type type;

        uint16_t x;
        uint16_t y;
        uint16_t fixed_x;
        uint16_t fixed_y;
        uint16_t width;
        uint16_t height;

        uint8_t key;
        bool selected;
        bool period;

        TypeBox(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Type type);
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};