#pragma once
#include "Global.hpp"

constexpr uint8_t BUTTON_SIZE{16};

class Button
{
    private:
        Global::Spritesheet spr;

        float scale;

        uint16_t x;
        uint16_t y;

        uint8_t type;
        uint8_t frame;

        void Texture();
        
    public:
        Button(uint16_t x = 0, uint16_t y = 0, uint8_t type = 0, uint8_t frame = 0, float scale = 1.0f);
        void Draw();
        void Update();
};