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

        Type type;

        uint16_t x;
        uint16_t y;
        uint16_t wheel_y;
        uint16_t width;
        uint16_t height;
        uint16_t wheel_length;
        int16_t wheel_power{};

        uint8_t id;
        uint8_t scale;
        uint8_t category;

        bool visible;
        bool holding;
        bool enabled;

        Window(uint16_t x = 0, uint16_t y = 0, uint16_t width = 0, uint16_t height = 0, uint8_t id = 0, Type type = Type::NORMAL_WINDOW, uint8_t scale = 1, Color bg_color = WHITE, Color outline_color = BLACK, bool enabled = true, uint8_t category = 0);
        void Draw(const std::function<void()>& Render) const;
        void Update();
        void UpdateCursor(uint16_t old_y, uint16_t old_height);
};