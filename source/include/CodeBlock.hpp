#pragma once
#include "Global.hpp"

#define BLOCK_SIZE  9

class Block
{
    private:
        Global::Spritesheet spr;

        void Texture(float _x, float _width, float _height, float _offset_x);

    public:
        float scale;

        int16_t x;
        int16_t y;
        int16_t offset_x;
        int16_t offset_y;
        uint16_t width;
        uint16_t height;

        bool held;

        Block(uint16_t x, uint16_t y, float scale);
        void Draw();
        void Update();
};