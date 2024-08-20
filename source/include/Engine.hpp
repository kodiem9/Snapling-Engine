#pragma once
#include "Window.hpp"
#include "Button.hpp"

enum ButtonTrigger
{
    FULLSCREEN = 1,
    BIGGER_WINDOW,
    SMALLER_WINDOW,
    NEW_SPRITE
};

enum WindowId
{
    GAME_WINDOW,
    PROPERTIES_WINDOW,
    SPRITES_WINDOW
};

#define WINDOW_OUTLINE_COLOR Color{ 195, 204, 217, 255 }
#define WINDOWS_UNIQUE_BG_COLOR Color{ 231, 240, 252, 255 }

class Engine
{
    public:
        Engine();
        ~Engine();
        void Draw();
        void Update();
    
    private:
        std::vector<Window> windows;
        std::vector<Button> buttons;
        
        uint16_t popup_x;
        uint16_t popup_y;
        uint16_t popup_width;
        uint16_t popup_height;

        uint8_t window_scale_mode;
        uint8_t saved_window_scale_mode;

        bool popup;

        void WindowAndButtonOffsets();
        void FullscreenOffsets();
        void BiggerWindowOffsets();
        void SmallerWindowOffsets();
};