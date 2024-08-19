#pragma once
#include "common/PCH.hpp"

namespace Global
{
    inline Texture2D button_texture;
    inline uint8_t button_pressed = 0;

    struct Spritesheet
    {
        Rectangle source;
        Rectangle dest;
        Vector2 origin;
    };

    inline void LoadTextures()
    {
        button_texture = LoadTexture("assets/images/buttons.png");
    }

    inline void UnloadTextures()
    {
        UnloadTexture(button_texture);
    }
};