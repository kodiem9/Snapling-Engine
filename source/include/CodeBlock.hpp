#pragma once
#include "Global.hpp"

#define BLOCK_SIZE  9

class Block
{
    private:
        Global::Spritesheet spr;

        void Texture(float _x, float _width, float _height, float _offset_x, float _offset_width, float _offset_width_x);

    public:
        enum class Type
        {
            NORMAL_BLOCK,
            PANEL_BLOCK,
            PLACEMENT_BLOCK
        };

        std::string text;

        Color color;

        Type type;
        float scale;

        int16_t x;
        int16_t y;
        int16_t fixed_x;
        int16_t fixed_y;
        int16_t offset_x;
        int16_t offset_y;
        uint16_t width;
        uint16_t id;

        uint8_t block_type;
        bool held;
        bool remove;

        Block(uint16_t x, uint16_t y, float scale, Type type, std::string text, uint16_t id = 0, uint8_t block_type = 0, Color color = WHITE);
        void Draw(int16_t window_x, int16_t window_y);
        void Update();
        void Data();
};