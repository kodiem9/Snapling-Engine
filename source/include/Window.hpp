#pragma once
#include "Global.hpp"

class Window
{
    public:
        enum class Type
        {
            NORMAL_WINDOW,
            SCROLL_WINDOW
        };

        Color bg_color;
        Color outline_color;
        Color wheel_color;

        Type type;

        uint16_t x;
        uint16_t y;
        uint16_t wheel_y;
        uint16_t width;
        uint16_t height;

        uint8_t id;
        uint8_t scale;

        bool visible;

        Window(uint16_t x = 0, uint16_t y = 0, uint16_t width = 0, uint16_t height = 0, uint8_t id = 0, Type type = Type::NORMAL_WINDOW, uint8_t scale = 1, Color bg_color = WHITE, Color outline_color = BLACK);
        void Draw(const std::function<void()>& Render);
        void Update();
        void UpdateData();
};