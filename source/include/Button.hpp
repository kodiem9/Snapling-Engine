#pragma once
#include "Global.hpp"

constexpr uint8_t BUTTON_SIZE{16};

class Button
{
    public:
        enum class Type
        {
            SINGLE_BUTTON,
            CHECKBOX
        };

        Type type;
        float scale;

        uint16_t x;
        uint16_t y;

        uint8_t trigger;
        uint8_t frame;

        bool selected;
        bool pressed;
        bool visible;

        Button(uint16_t x = 0, uint16_t y = 0, uint8_t trigger = 0, Type type = Type::SINGLE_BUTTON, uint8_t frame = 0, float scale = 1.0f);
        void Draw();
        void Update();
    
    private:
        Global::Spritesheet spr;

        void Texture();
};