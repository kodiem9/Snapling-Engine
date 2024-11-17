#pragma once
#include <PCH.hpp>

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
        
        int x;
        int y;
        int direction;

        uint16_t size;

        bool show;
        uint8_t direction_mode;


        ObjectData(std::string name = "", float x = 0.0f, float y = 0.0f, float direction = 0.0f, uint16_t size = 0, bool show = false, uint8_t direction_mode = 0)
        : name(name), x(x), y(y), direction(direction), size(size), show(show), direction_mode(direction_mode) {}
    };

    struct FTexture
    {
        Texture2D texture;
        uint8_t width;
        uint8_t height;
    };

    inline std::vector<ObjectData> entities;

    inline FTexture button_texture;
    inline FTexture category_button_texture;
    inline FTexture blocks_texture;

    inline std::vector<Color> block_colors;
    inline std::vector<Vector2> block_grid_position;
    inline std::vector<uint8_t> selected_costumes;

    inline float code_panel_scale = 4.0f;
    inline float coding_grid_scale = 3.0f;

    inline uint16_t screen_width;
    inline uint16_t screen_height;
    inline uint16_t game_window_width = 0;
    inline uint16_t game_window_height = 0;
    inline uint16_t coding_window_width = 0;
    inline uint16_t coding_window_x = 0;
    inline uint16_t coding_panels_width = 0;
    inline uint16_t assets_window_x = 0;
    inline uint16_t assets_window_width = 0;
    inline uint16_t costumes_window_width = 0;
    inline uint16_t selected_panel_block = 0;
    inline uint16_t blocks_amount;

    inline uint8_t game_scale = 10;
    inline uint8_t button_pressed = 0;
    inline uint8_t sprites_amount = 0;
    inline uint8_t selected_sprite = 0;
    inline uint8_t selected_block_type = 0;
    inline uint8_t block_type_amount = 0;
    inline uint8_t current_category = 1;
    inline uint8_t category_amount = 0;
    inline bool execute_new_block = false;
    inline bool holding_block = false;

    inline bool MouseCollision(int x, int y, int width, int height)
    {
        return GetMouseX() > x && GetMouseX() < x + width && GetMouseY() > y && GetMouseY() < y + height;
    }

    inline void LoadTextures()
    {
        button_texture.texture = LoadTexture("../assets/images/buttons.png");
        button_texture.width = 16;
        button_texture.height = 16;

        category_button_texture.texture = LoadTexture("../assets/images/category_buttons.png");
        category_button_texture.width = 24;
        category_button_texture.height = 8;

        blocks_texture.texture = LoadTexture("../assets/images/blocks.png");
        blocks_texture.width = 9;
        blocks_texture.height = 9;
    }

    inline void UnloadTextures()
    {
        UnloadTexture(button_texture.texture);
        UnloadTexture(blocks_texture.texture);
        UnloadTexture(category_button_texture.texture);
    }
};