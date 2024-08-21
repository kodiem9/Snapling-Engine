#include "include/Engine.hpp"


// PUBLIC
Engine::Engine()
{
    Global::LoadTextures();
    window_scale_mode = 0;
    saved_window_scale_mode = 0;
    tween_timer = 0.0f;

    new_sprite_popup = new PopUp(GetScreenWidth() - 109, GetScreenHeight() - 167, 48, 56, POPUP_COLOR);

    // The windows enum is IN ORDER! So GAME_WINDOW is 0, first index in the vector is the game window, etc.
    windows.emplace_back(GetScreenWidth() - 640, 40, 60, 45, WindowId::GAME_WINDOW, Window::Type::NORMAL_WINDOW, 10, WHITE, WINDOW_OUTLINE_COLOR);
    windows.emplace_back(GetScreenWidth() - 640, 500, 60, 15, WindowId::PROPERTIES_WINDOW, Window::Type::NORMAL_WINDOW, 10, WHITE, WINDOW_OUTLINE_COLOR);
    windows.emplace_back(GetScreenWidth() - 640, 650, 60, (GetScreenHeight() - 650) / 10 - 10, WindowId::SPRITES_WINDOW, Window::Type::SCROLL_WINDOW, 10, WINDOWS_UNIQUE_BG_COLOR, WINDOW_OUTLINE_COLOR);
    sprite_window_height = windows[2].height * windows[2].scale;

    // Buttons are random lol.
    buttons.emplace_back(GetScreenWidth() - 72, 4, ButtonTrigger::FULLSCREEN, Button::Type::SINGLE_BUTTON, 0, 2.0f);
    buttons.emplace_back(GetScreenWidth() - 120, 4, ButtonTrigger::BIGGER_WINDOW, Button::Type::SINGLE_BUTTON, 1, 2.0f);
    buttons.emplace_back(GetScreenWidth() - 152, 4, ButtonTrigger::SMALLER_WINDOW, Button::Type::SINGLE_BUTTON, 2, 2.0f);
    buttons.emplace_back(GetScreenWidth() - 109, GetScreenHeight() - 159, ButtonTrigger::EMPTY_SPRITE, Button::Type::SINGLE_BUTTON, 4, 3.0f);
    buttons.emplace_back(GetScreenWidth() - 117, GetScreenHeight() - 175, ButtonTrigger::NEW_SPRITE, Button::Type::SINGLE_BUTTON, 3, 4.0f);
}

Engine::~Engine()
{
    Global::UnloadTextures();
}

void Engine::Draw()
{
    for(Window &window: windows) {
        switch(window.type)
        {
            case Window::Type::SCROLL_WINDOW: {
                window.Draw([&]() {
                    for(Sprite &sprite: sprites) {
                        sprite.Draw(window.x, window.y - windows[2].wheel_power);
                    }
                });
            }
            break;

            case Window::Type::NORMAL_WINDOW: window.Draw([&](){}); break;

            default: break;
        }
    }

    new_sprite_popup->Draw();
    
    for(Button &button: buttons) {
        button.Draw();
    }

    if(IsKeyDown(KeyboardKey::KEY_TAB)) {
        DrawFPS(10, 10);
    }
}

void Engine::Update()
{
    for(Window &window: windows) {
        window.Update();
    }

    PopUpUpdate();

    for(Button &button: buttons) {
        button.Update();
    }

    for(Sprite &sprite: sprites) {
        sprite.Update();
    }

    ButtonUpdate();

    if(tween_timer > 0.0f) {
        tween_timer -= GetFrameTime();
        if(tween_timer < 0.0f) tween_timer = 0.0f;
    }
}


// PRIVATE
inline void Engine::NewSprite(std::vector<Sprite> &sprites, uint16_t loop, uint8_t offset, uint8_t row)
{
    uint16_t fixed_x_offset;
    uint16_t fixed_y_offset;
    for(uint16_t i = 0; i < loop; i++) {
        fixed_x_offset = (Global::sprites_amount % row) * 100;
        fixed_y_offset = (Global::sprites_amount / row) * 100;
        sprites.emplace_back(offset + fixed_x_offset, 20 + fixed_y_offset, 80, 80, Global::sprites_amount);
        Global::sprites_amount++;
    }
    if(100 + fixed_y_offset > sprite_window_height) {
        windows[2].wheel_length = 120 + fixed_y_offset - sprite_window_height;
    }
}

inline void Engine::PopUpUpdate()
{
    if(tween_timer > 0.0f) {
        if(new_sprite_popup->enabled) {
            new_sprite_popup->Scroll(new_sprite_popup->y, GetScreenHeight() - 371, 6);
            new_sprite_popup->Scroll(new_sprite_popup->height, 200, 6);

            // Button offsets on pop up
            for(Button &button: buttons)
            {
                switch(button.trigger)
                {
                    case ButtonTrigger::EMPTY_SPRITE: {
                        button.y += ((GetScreenHeight() - 239) - button.y) / 7;
                    }
                    break;

                    default: break;
                }
            }
        }
        else {
            new_sprite_popup->Scroll(new_sprite_popup->y, GetScreenHeight() - 167, 6);
            new_sprite_popup->Scroll(new_sprite_popup->height, 56, 6);

            // Button offsets on pop up
            for(Button &button: buttons)
            {
                switch(button.trigger)
                {
                    case ButtonTrigger::EMPTY_SPRITE: {
                        button.y += ((GetScreenHeight() - 159) - button.y) / 7;
                    }
                    break;

                    default: break;
                }
            }
        }
    }
}

void Engine::ButtonUpdate()
{
    switch(Global::button_pressed)
    {
        case ButtonTrigger::FULLSCREEN: FullscreenOffsets(); break;

        case ButtonTrigger::BIGGER_WINDOW: {
            BiggerWindowOffsets();
            SpritesOffsets();
        }
        break;

        case ButtonTrigger::SMALLER_WINDOW: {
            SmallerWindowOffsets();
            SpritesOffsets();   
        }
        break;

        case ButtonTrigger::NEW_SPRITE: {
            tween_timer = 1.0f;
            new_sprite_popup->enabled = !new_sprite_popup->enabled;
            Global::button_pressed = 0;
        }
        break;

        case ButtonTrigger::EMPTY_SPRITE: {
            if(window_scale_mode == 1)
                NewSprite(sprites, 1, 10, 3);
            else
                NewSprite(sprites, 1, 20, 5);

            Global::button_pressed = 0;
        }
        break;

        default: break;
    }
}


// OFFSETS
// All of this is just a bunch of offsets. You should probably not touch this ngl.
void Engine::FullscreenOffsets()
{
    Window &game_window = windows[WindowId::GAME_WINDOW];

    if(window_scale_mode != 2) {
        saved_window_scale_mode = window_scale_mode;
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::GAME_WINDOW: {
                    window.scale = 17;
                    window.y = (GetScreenHeight() - window.height * window.scale) / 2 - 28;
                    window.x = (GetScreenWidth() - window.width * window.scale) / 2;
                }
                break;

                case WindowId::PROPERTIES_WINDOW: window.visible = false; break;
                case WindowId::SPRITES_WINDOW: window.visible = false; break;

                default: break;
            }
        }

        for(Button &button: buttons) {
            switch(button.trigger)
            {
                case ButtonTrigger::FULLSCREEN: {
                    button.x = game_window.x + (game_window.width * game_window.scale) - BUTTON_SIZE * button.scale;
                }
                break;

                case ButtonTrigger::SMALLER_WINDOW: button.visible = false; break;
                case ButtonTrigger::BIGGER_WINDOW: button.visible = false; break;
                case ButtonTrigger::NEW_SPRITE: button.visible = false; break;
                case ButtonTrigger::EMPTY_SPRITE: button.visible = false; break;
            }
        }
        new_sprite_popup->visible = false;
        window_scale_mode = 2;
    }
    else {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::GAME_WINDOW: {
                    if(saved_window_scale_mode == 0)
                        window.scale = 10;
                    else
                        window.scale = 5;
                    
                    window.y = 40;
                    window.x = (GetScreenWidth() - (window.width * window.scale) - 40);
                }
                break;

                case WindowId::PROPERTIES_WINDOW: window.visible = true; break;
                case WindowId::SPRITES_WINDOW: window.visible = true; break;

                default: break;
            }
        }
        for(Button &button: buttons) {
            switch(button.trigger)
            {
                case ButtonTrigger::FULLSCREEN: {
                    button.x = GetScreenWidth() - 72;
                }
                break;

                case ButtonTrigger::SMALLER_WINDOW: button.visible = true; break;
                case ButtonTrigger::BIGGER_WINDOW: button.visible = true; break;
                case ButtonTrigger::NEW_SPRITE: button.visible = true; break;
                case ButtonTrigger::EMPTY_SPRITE: button.visible = true; break;
            }
        }
        window_scale_mode = saved_window_scale_mode;
        new_sprite_popup->visible = true;
    }
    Global::button_pressed = 0;
}

void Engine::BiggerWindowOffsets()
{
    if(window_scale_mode == 1) {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::GAME_WINDOW: {
                    window.x -= window.width * window.scale;
                    window.scale = 10;
                }
                break;

                case WindowId::PROPERTIES_WINDOW: {
                    window.x -= window.width * window.scale;
                    window.y += 225; // difference between big and small game window
                    window.scale = 10;
                }
                break;

                case WindowId::SPRITES_WINDOW: {
                    uint16_t old_y = window.y;
                    uint16_t old_height = window.height * window.scale;
                    
                    window.x -= window.width * window.scale;
                    window.y += 300; // difference between big and small game window PLUS half the height * scale of properties window 
                    window.scale = 10;
                    window.height = (GetScreenHeight() - window.y) / 10 - 10; // some weird math idk why this works

                    window.UpdateCursor(old_y, old_height);
                    sprite_window_height = window.height * window.scale;
                }
                break;

                default: break;
            }
        }
        window_scale_mode = 0;
    }
    Global::button_pressed = 0;
}

void Engine::SmallerWindowOffsets()
{
    if(window_scale_mode == 0) {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::GAME_WINDOW: {
                    window.scale = 5;
                    window.x += window.width * window.scale;
                }
                break;

                case WindowId::PROPERTIES_WINDOW: {
                    window.scale = 5;
                    window.x += window.width * window.scale;
                    window.y -= 225; // difference between big and small game window
                }
                break;

                case WindowId::SPRITES_WINDOW: {
                    uint16_t old_y = window.y;
                    uint16_t old_height = window.height * window.scale;

                    window.scale = 5;
                    window.x += window.width * window.scale;
                    window.y -= 300; // difference between big and small game window PLUS half the height * scale of properties window 
                    window.height = (GetScreenHeight() - window.y) / 5 - 20; // some weird math idk why this works

                    window.UpdateCursor(old_y, old_height);
                    sprite_window_height = window.height * window.scale;
                }
                break;

                default: break;
            }
        }
        window_scale_mode = 1;
    }
    Global::button_pressed = 0;
}

void Engine::SpritesOffsets()
{
    std::vector<Sprite> new_sprites;
    uint16_t fixed_x_offset;
    uint16_t fixed_y_offset;
    Global::sprites_amount = 0;

    if(window_scale_mode == 1)
        NewSprite(new_sprites, sprites.size(), 10, 3);
    else
        NewSprite(new_sprites, sprites.size(), 20, 5);

    sprites = new_sprites;
}