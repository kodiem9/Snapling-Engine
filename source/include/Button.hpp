#pragma once
#include "Global.hpp"
#include <stdio.h>

constexpr uint8_t BUTTON_SIZE{16};

class Button
{
    public:
        enum class Type
        {
            SINGLE_BUTTON,
            CHECKBOX
        };

        Button(uint16_t x = 0, uint16_t y = 0, uint8_t trigger = 0, Type type = Type::SINGLE_BUTTON, uint8_t frame = 0, float scale = 1.0f);
        void Draw();
        void Update();
    
    private:
        Global::Spritesheet spr;

        float scale;
        Type type;

        uint16_t x;
        uint16_t y;

        uint8_t trigger;
        uint8_t frame;

        bool selected;
        bool pressed;

        void Texture();
};