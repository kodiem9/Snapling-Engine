#pragma once
#include "common/PCH.hpp"

namespace Global
{
    struct Spritesheet
    {
        Rectangle source;
        Rectangle dest;
        Vector2 origin;
    };

    struct ObjectData
    {
        std::string name;
        
        float x;
        float y;
        float direction;

        uint16_t size;

        bool show;
        uint8_t direction_mode;
    };

    inline Texture2D button_texture;
    inline ObjectData selected_sprite_data;
    inline uint8_t button_pressed = 0;
    inline uint8_t sprites_amount = 0;
    inline uint8_t selected_sprite = 0;

    inline bool MouseCollision(int x, int y, int width, int height)
    {
        return GetMouseX() > x && GetMouseX() < x + width && GetMouseY() > y && GetMouseY() < y + height;
    }

    inline void LoadTextures()
    {
        button_texture = LoadTexture("assets/images/buttons.png");
    }

    inline void UnloadTextures()
    {
        UnloadTexture(button_texture);
    }
};