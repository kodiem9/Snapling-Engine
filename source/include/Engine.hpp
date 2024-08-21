#pragma once
#include "Window.hpp"
#include "Button.hpp"
#include "PopUp.hpp"
#include "Sprite.hpp"

enum ButtonTrigger
{
    FULLSCREEN = 1,
    BIGGER_WINDOW,
    SMALLER_WINDOW,
    NEW_SPRITE,
    EMPTY_SPRITE
};

enum WindowId
{
    GAME_WINDOW,
    PROPERTIES_WINDOW,
    SPRITES_WINDOW
};

#define WINDOW_OUTLINE_COLOR Color{ 195, 204, 217, 255 }
#define WINDOWS_UNIQUE_BG_COLOR Color{ 231, 240, 252, 255 }

#define POPUP_COLOR Color{ 177, 62, 83, 180 }

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
        std::vector<Sprite> sprites;
        
        PopUp *new_sprite_popup;

        float tween_timer;

        uint16_t sprite_window_height;

        uint8_t window_scale_mode;
        uint8_t saved_window_scale_mode;

        inline void PopUpUpdate();
        void ButtonUpdate();
        void FullscreenOffsets();
        void BiggerWindowOffsets();
        void SmallerWindowOffsets();
};