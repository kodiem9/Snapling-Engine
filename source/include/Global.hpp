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


        ObjectData(std::string name = "", float x = 0.0f, float y = 0.0f, float direction = 0.0f, uint16_t size = 0, bool show = false, uint8_t direction_mode = 0)
        : name(name), x(x), y(y), direction(direction), size(size), show(show), direction_mode(direction_mode) {}
    };

    inline std::vector<ObjectData> entities;

    inline Texture2D button_texture;
    inline Texture2D blocks_texture;

    inline uint16_t game_window_width = 0;
    inline uint16_t game_window_height = 0;
    inline uint16_t coding_window_width = 0;
    inline uint16_t coding_panels_width = 0;

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
        blocks_texture = LoadTexture("assets/images/blocks.png");
    }

    inline void UnloadTextures()
    {
        UnloadTexture(button_texture);
        UnloadTexture(blocks_texture);
    }
};