#pragma once
#include "Global.hpp"

class Button
{
    public:
        enum class Type
        {
            SINGLE_BUTTON,
            CHECKBOX
        };

        Global::FTexture *texture;

        Type type;
        float scale;

        uint16_t x;
        uint16_t y;

        uint8_t trigger;
        uint8_t frame;
        uint8_t *checkbox;
        uint8_t value;

        bool selected;
        bool pressed;
        bool visible;
        bool toggled;

        Button(uint16_t x = 0, uint16_t y = 0, uint8_t trigger = 0, Type type = Type::SINGLE_BUTTON, uint8_t frame = 0, float scale = 1.0f, Global::FTexture *texture = NULL, uint8_t *checkbox = nullptr, uint8_t value = 0);
        void Draw();
        void Update();
    
    private:
        Global::Spritesheet spr;

        void Texture();
};