#include "include/Engine.hpp"


// PUBLIC
Engine::Engine()
{
    Global::LoadTextures();
    window_scale_mode = WindowScaleModes::BIGGER_WINDOW_MODE;
    saved_window_scale_mode = window_scale_mode;
    tween_timer = 0.0f;
    code_panels_mode = true;

    new_sprite_popup = new PopUp(GetScreenWidth() - 79, GetScreenHeight() - 167, 48, 56, POPUP_COLOR);
    properties_box = new PropertiesBox;
    // This isn't a vector of entities. It's more of a template. The entities data is actually inside "Global.hpp".
    // I made this entity class for it to be clean (just like the PopUp class)
    entity = new Entity;
    block_type_panel = new BlockTypePanel;
    dragged_block = new Block(10, 10, Global::code_panel_scale, Block::Type::PLACEMENT_BLOCK, "Testing");
    panel_blocks = new PanelBlocks(dragged_block);


    // The windows enum is IN ORDER! So GAME_WINDOW is 0, first index in the vector is the game window, etc.
    Global::game_scale = 10;
    windows.emplace_back(GetScreenWidth() - 610, 40, 60, 45, WindowId::GAME_WINDOW, Window::Type::NORMAL_WINDOW, Global::game_scale, WHITE, WINDOW_OUTLINE_COLOR, true, 0);
    Global::game_window_width = windows[WindowId::GAME_WINDOW].width * windows[WindowId::GAME_WINDOW].scale;
    Global::game_window_height = windows[WindowId::GAME_WINDOW].height * windows[WindowId::GAME_WINDOW].scale;

    windows.emplace_back(GetScreenWidth() - 610, 500, 60, 15, WindowId::PROPERTIES_WINDOW, Window::Type::NORMAL_WINDOW, 10, WHITE, WINDOW_OUTLINE_COLOR, false, 0);

    windows.emplace_back(GetScreenWidth() - 610, 650, 60, (GetScreenHeight() - 650) / 10 - 10, WindowId::SPRITES_WINDOW, Window::Type::SCROLL_WINDOW, 10, WINDOWS_UNIQUE_BG_COLOR, WINDOW_OUTLINE_COLOR, true, 0);
    sprite_window_height = windows[WindowId::SPRITES_WINDOW].height * windows[WindowId::SPRITES_WINDOW].scale;

    Global::coding_window_x = 280;
    Global::coding_window_width = GetScreenWidth() - Global::game_window_width - (Global::coding_window_x + 20);
    windows.emplace_back(Global::coding_window_x, 40, Global::coding_window_width, GetScreenHeight() - 140, WindowId::CODING_WINDOW, Window::Type::NORMAL_WINDOW, 1, WHITE, WINDOW_OUTLINE_COLOR, true, WindowCategory::CATEGORY_CODE);

    Global::coding_panels_width = GetScreenWidth() - Global::game_window_width - Global::coding_window_width - 30;
    windows.emplace_back(10, 40, Global::coding_panels_width, (GetScreenHeight() / 5) * 2 - 80, WindowId::BLOCK_TYPE_WINDOW, Window::Type::NORMAL_WINDOW, 1, WINDOW_CODE_PANEL_COLOR, WINDOW_OUTLINE_COLOR, false, WindowCategory::CATEGORY_CODE);
    windows.emplace_back(10, 40 + (GetScreenHeight() / 5) * 2 - 80, Global::coding_panels_width, (GetScreenHeight() / 5) * 3 - 60, WindowId::BLOCK_PANEL_WINDOW, Window::Type::NORMAL_WINDOW, 1, WINDOW_CODE_PANEL_COLOR, WINDOW_OUTLINE_COLOR, true, WindowCategory::CATEGORY_CODE);

    Global::assets_window_x = 10;
    Global::assets_window_width = GetScreenWidth() - Global::game_window_width - (Global::assets_window_x + 20);
    windows.emplace_back(Global::assets_window_x, 40, Global::assets_window_width, GetScreenHeight() - 140, WindowId::ASSETS_WINDOW, Window::Type::NORMAL_WINDOW, 1, WHITE, WINDOW_OUTLINE_COLOR, true, WindowCategory::CATEGORY_ASSETS);
    windows[WindowId::ASSETS_WINDOW].visible = false;


    // Lonely grid...
    grid = new Grid;


    // Buttons are random lol, but also not! Depends. You better be careful with this.
    buttons.emplace_back(GetScreenWidth() - 42, 4, ButtonTrigger::FULLSCREEN, Button::Type::SINGLE_BUTTON, 0, 2.0f, &Global::button_texture);
    buttons.emplace_back(GetScreenWidth() - 90, 4, ButtonTrigger::BIGGER_WINDOW, Button::Type::CHECKBOX, 1, 2.0f, &Global::button_texture, &window_scale_mode, WindowScaleModes::BIGGER_WINDOW_MODE);
    buttons.emplace_back(GetScreenWidth() - 122, 4, ButtonTrigger::SMALLER_WINDOW, Button::Type::CHECKBOX, 2, 2.0f, &Global::button_texture, &window_scale_mode, WindowScaleModes::SMALLER_WINDOW_MODE);
    buttons.emplace_back(GetScreenWidth() - 79, GetScreenHeight() - 159, ButtonTrigger::EMPTY_SPRITE, Button::Type::SINGLE_BUTTON, 5, 3.0f, &Global::button_texture);
    buttons.emplace_back(GetScreenWidth() - 87, GetScreenHeight() - 175, ButtonTrigger::NEW_SPRITE, Button::Type::SINGLE_BUTTON, 4, 4.0f, &Global::button_texture);
    buttons.emplace_back(10, GetScreenHeight() - 92, ButtonTrigger::BLOCK_PANELS, Button::Type::SINGLE_BUTTON, 3, 2.0f, &Global::button_texture);


    // Category buttons (code, assets, sounds, etc.)
    categories.emplace_back("Code", ButtonTrigger::CODE_CATEGORY);
    categories.emplace_back("Assets", ButtonTrigger::ASSETS_CATEGORY);
}

Engine::~Engine()
{
    Global::UnloadTextures();

    delete new_sprite_popup;
    delete panel_blocks;
    delete entity;
    delete dragged_block;
    delete grid;
    delete block_type_panel;
}

void Engine::Draw()
{
    for(Window &window: windows) {
        switch(window.id)
        {
            case WindowId::GAME_WINDOW: {
                window.Draw([&]() {
                    for(uint8_t i = 0; i < Global::sprites_amount; i++) {
                        entity->Draw(window.x, window.y, i);
                    }
                });
            }
            break;

            case WindowId::PROPERTIES_WINDOW: {
                window.Draw([&]() {
                    if(Global::sprites_amount > 0) {
                        properties_box->Draw(window.x, window.y);
                    }
                });
            }
            break;

            case WindowId::SPRITES_WINDOW: {
                window.Draw([&]() {
                    for(Sprite &sprite: sprites) {
                        sprite.Draw(window.x, window.y - windows[2].wheel_power);
                    }
                });
            }
            break;

            case WindowId::CODING_WINDOW: {
                window.Draw([&]() {
                    if(Global::sprites_amount > 0) {
                        grid->Draw(window.x, window.y);
                        for(Block &block: blocks[Global::selected_sprite]) {
                            block.Draw(window.x - Global::block_grid[Global::selected_sprite].x, window.y - Global::block_grid[Global::selected_sprite].y);
                        }
                        DrawText(TextFormat("(%.0f, %.0f)", Global::block_grid[Global::selected_sprite].x, Global::block_grid[Global::selected_sprite].y), 10 + window.x, window.height - 30 + window.y, 20, LIGHTGRAY);
                    }
                });
            }
            break;

            case WindowId::BLOCK_PANEL_WINDOW: {
                window.Draw([&]() {
                    if(Global::sprites_amount > 0) {
                        panel_blocks->Draw(window.x, window.y);
                    }
                });
            }
            break;

            case WindowId::BLOCK_TYPE_WINDOW: {
                window.Draw([&]() {
                    if(Global::sprites_amount > 0) {
                        block_type_panel->Draw(window.x, window.y);
                    }
                });
            }
            break;

            default: window.Draw([&](){}); break;
        }
    }

    new_sprite_popup->Draw();

    if(Global::selected_panel_block > 0) {
        dragged_block->Draw(0, 0);
    }

    for(Category &category: categories) {
        category.Draw();
    }

    for(Button &button: buttons) {
        button.Draw();
    }

    if(IsKeyDown(KeyboardKey::KEY_TAB)) {
        DrawFPS(10, 10);
        DrawText(TextFormat("Sprites: %i\n", Global::sprites_amount), 10, 40, 25, RED);
        DrawText(TextFormat("Blocks: %i\n", Global::blocks_amount), 10, 70, 25, BLUE);
    }
}

void Engine::Update()
{
    for(Window &window: windows) {
        window.Update();
    }

    PopUpUpdate();

    for(Category &category: categories) {
        category.Update();
    }

    for(Button &button: buttons) {
        button.Update();
    }

    for(Sprite &sprite: sprites) {
        sprite.Update();
    }

    if(Global::sprites_amount > 0) {
        for(auto block = blocks[Global::selected_sprite].begin(); block < blocks[Global::selected_sprite].end(); ++block) {
            block->Update();

            if(block->remove) {
                Global::blocks_amount--;
                blocks[Global::selected_sprite].erase(block);
            }
        }
    }

    if(Global::sprites_amount > 0) {
        properties_box->Update();
    }

    ButtonUpdate();

    if(Global::sprites_amount > 0) {
        grid->Update();
        panel_blocks->Update();
        block_type_panel->Update();
    }

    if(Global::selected_panel_block > 0) {
        dragged_block->Update();
    }

    if(Global::execute_new_block) {
        Global::blocks_amount++;
        blocks[Global::selected_sprite].emplace_back(dragged_block->x - Global::coding_panels_width + Global::block_grid[Global::selected_sprite].x, dragged_block->y - 40 + Global::block_grid[Global::selected_sprite].y, Global::coding_grid_scale, Block::Type::NORMAL_BLOCK, dragged_block->text, 0, dragged_block->block_type);
        Global::execute_new_block = false;
    }

    if(tween_timer > 0.0f) {
        tween_timer -= GetFrameTime();
        if(tween_timer < 0.0f) tween_timer = 0.0f;
    }

    Commands();
}


// PRIVATE
inline void Engine::NewSprite(std::vector<Sprite> &sprites, uint16_t loop, uint8_t offset, uint8_t row, bool upd_curr_spr)
{
    uint16_t fixed_x_offset = 0;
    uint16_t fixed_y_offset = 0;
    windows[2].wheel_length = 0;
    for(uint16_t i = 0; i < loop; i++) {
        fixed_x_offset = (Global::sprites_amount % row) * 100;
        fixed_y_offset = (Global::sprites_amount / row) * 100;
        sprites.emplace_back(offset + fixed_x_offset, 20 + fixed_y_offset, 80, 80, Global::sprites_amount, upd_curr_spr);
        Global::sprites_amount++;
    }
    if(100 + fixed_y_offset > sprite_window_height) {
        windows[2].wheel_length = 120 + fixed_y_offset - sprite_window_height;
    }
    blocks.push_back(std::vector<Block>());
    Global::block_grid.push_back(Vector2{ 0, 0 });
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

void Engine::Commands()
{
    if(IsKeyPressed(KeyboardKey::KEY_R) && IsKeyDown(KeyboardKey::KEY_LEFT_CONTROL)) {
        for(std::vector<Block> &block: blocks) {
            block.shrink_to_fit();
        }
        blocks.shrink_to_fit();
    }

    if(IsKeyPressed(KeyboardKey::KEY_ZERO)) {
        printf("%i\n", Global::current_category);
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
            properties_box->Reset(1);
            grid->Data();
        }
        break;

        case ButtonTrigger::SMALLER_WINDOW: {
            SmallerWindowOffsets();
            SpritesOffsets();   
            properties_box->Reset(0);
            grid->Data();
        }
        break;

        case ButtonTrigger::NEW_SPRITE: {
            tween_timer = 1.0f;
            new_sprite_popup->enabled = !new_sprite_popup->enabled;
            Global::button_pressed = 0;
        }
        break;

        case ButtonTrigger::EMPTY_SPRITE: {
            Global::entities.emplace_back("Sprite", 0.0f, 0.0f, 90.0f, 100, true, 0);
            if(window_scale_mode == WindowScaleModes::SMALLER_WINDOW_MODE)
                NewSprite(sprites, 1, 10, 3, true);
            else
                NewSprite(sprites, 1, 20, 5, true);

            Global::button_pressed = 0;
        }
        break;

        case ButtonTrigger::BLOCK_PANELS: {
            BlockPanelsOffsets();
            grid->Data();
        }
        break;

        case ButtonTrigger::CODE_CATEGORY: CodeCategoryOffsets(); break;
        case ButtonTrigger::ASSETS_CATEGORY: AssetsCategoryOffsets(); break;

        default: break;
    }
}


// OFFSETS
// All of this is just a bunch of offsets. You should probably not touch this ngl.
void Engine::FullscreenOffsets()
{
    Window &game_window = windows[WindowId::GAME_WINDOW];

    if(window_scale_mode != WindowScaleModes::FULLSCREEN_MODE) {
        saved_window_scale_mode = window_scale_mode;
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::GAME_WINDOW: {
                    window.scale = 17;
                    Global::game_scale = window.scale;
                    window.y = (GetScreenHeight() - window.height * window.scale) / 2 - 28;
                    window.x = (GetScreenWidth() - window.width * window.scale) / 2;
                    Global::game_window_width = window.width * window.scale;
                    Global::game_window_height = window.height * window.scale;
                }
                break;

                case WindowId::PROPERTIES_WINDOW: window.visible = false; break;
                case WindowId::SPRITES_WINDOW: window.visible = false; break;
                case WindowId::CODING_WINDOW: window.visible = false; break;
                case WindowId::BLOCK_TYPE_WINDOW: window.visible = false; break;
                case WindowId::BLOCK_PANEL_WINDOW: window.visible = false; break;
                case WindowId::ASSETS_WINDOW: window.visible = false; break;

                default: break;
            }
        }

        for(Button &button: buttons) {
            switch(button.trigger)
            {
                case ButtonTrigger::FULLSCREEN: {
                    button.x = game_window.x + (game_window.width * game_window.scale) - Global::button_texture.width * button.scale;
                }
                break;

                case ButtonTrigger::SMALLER_WINDOW: button.visible = false; break;
                case ButtonTrigger::BIGGER_WINDOW: button.visible = false; break;
                case ButtonTrigger::NEW_SPRITE: button.visible = false; break;
                case ButtonTrigger::EMPTY_SPRITE: button.visible = false; break;
                case ButtonTrigger::BLOCK_PANELS: button.visible = false; break;
            }
        }

        for(Category &category: categories) {
            switch(category.button.trigger)
            {
                case ButtonTrigger::CODE_CATEGORY: category.visible = false;
                case ButtonTrigger::ASSETS_CATEGORY: category.visible = false;
            }
        }

        new_sprite_popup->visible = false;
        window_scale_mode = WindowScaleModes::FULLSCREEN_MODE;
    }
    else {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::GAME_WINDOW: {
                    if(saved_window_scale_mode == WindowScaleModes::BIGGER_WINDOW_MODE)
                        window.scale = 10;
                    else
                        window.scale = 5;

                    Global::game_scale = window.scale;
                    
                    window.y = 40;
                    window.x = (GetScreenWidth() - (window.width * window.scale) - 10);

                    Global::game_window_width = window.width * window.scale;
                    Global::game_window_height = window.height * window.scale;
                }
                break;

                case WindowId::PROPERTIES_WINDOW: window.visible = true; break;
                case WindowId::SPRITES_WINDOW: window.visible = true; break;
                case WindowId::CODING_WINDOW: window.visible = (Global::current_category == WindowCategory::CATEGORY_CODE); break;
                case WindowId::BLOCK_TYPE_WINDOW: window.visible = (Global::current_category == WindowCategory::CATEGORY_CODE); break;
                case WindowId::BLOCK_PANEL_WINDOW: window.visible = (Global::current_category == WindowCategory::CATEGORY_CODE); break;
                case WindowId::ASSETS_WINDOW: window.visible = (Global::current_category == WindowCategory::CATEGORY_ASSETS); break;

                default: break;
            }
        }
        for(Button &button: buttons) {
            switch(button.trigger)
            {
                case ButtonTrigger::FULLSCREEN: {
                    button.x = GetScreenWidth() - 42;
                }
                break;

                case ButtonTrigger::SMALLER_WINDOW: button.visible = true; break;
                case ButtonTrigger::BIGGER_WINDOW: button.visible = true; break;
                case ButtonTrigger::NEW_SPRITE: button.visible = true; break;
                case ButtonTrigger::EMPTY_SPRITE: button.visible = true; break;
                case ButtonTrigger::BLOCK_PANELS: button.visible = true; break;
            }
        }

        for(Category &category: categories) {
            switch(category.button.trigger)
            {
                case ButtonTrigger::CODE_CATEGORY: category.visible = true;
                case ButtonTrigger::ASSETS_CATEGORY: category.visible = true;
            }
        }

        window_scale_mode = saved_window_scale_mode;
        new_sprite_popup->visible = true;
    }
    Global::button_pressed = 0;
}

void Engine::BiggerWindowOffsets()
{
    if(window_scale_mode != WindowScaleModes::BIGGER_WINDOW_MODE) {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::GAME_WINDOW: {
                    window.x -= window.width * window.scale;
                    window.scale = 10;

                    Global::game_window_width = window.width * window.scale;
                    Global::game_window_height = window.height * window.scale;
                    Global::game_scale = window.scale;
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

                case WindowId::CODING_WINDOW: {
                    window.width = GetScreenWidth() - Global::game_window_width - (window.x + 20);
                    Global::coding_window_width = window.width;
                }
                break;

                case WindowId::ASSETS_WINDOW: {
                    window.width = GetScreenWidth() - Global::game_window_width - (window.x + 20);
                    Global::assets_window_width = window.width;
                }
                break;

                default: break;
            }
        }
        window_scale_mode = WindowScaleModes::BIGGER_WINDOW_MODE;
    }
    Global::button_pressed = 0;
}

void Engine::SmallerWindowOffsets()
{
    if(window_scale_mode != WindowScaleModes::SMALLER_WINDOW_MODE) {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::GAME_WINDOW: {
                    window.scale = 5;
                    window.x += window.width * window.scale;

                    Global::game_window_width = window.width * window.scale;
                    Global::game_window_height = window.height * window.scale;
                    Global::game_scale = window.scale;
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

                case WindowId::CODING_WINDOW: {
                    window.width = GetScreenWidth() - windows[0].width * windows[0].scale - (window.x + 20);
                    Global::coding_window_width = window.width;
                }
                break;

                case WindowId::ASSETS_WINDOW: {
                    window.width = GetScreenWidth() - Global::game_window_width - (window.x + 20);
                    Global::assets_window_width = window.width;
                }
                break;

                default: break;
            }
        }
        window_scale_mode = WindowScaleModes::SMALLER_WINDOW_MODE;
    }
    Global::button_pressed = 0;
}

void Engine::BlockPanelsOffsets()
{
    code_panels_mode = !code_panels_mode;
    if(code_panels_mode) {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::CODING_WINDOW: {
                    window.x = 280;
                    window.width = GetScreenWidth() - Global::game_window_width - (window.x + 20);
                    Global::coding_window_width = window.width;
                    Global::coding_window_x = window.x;
                }
                break;

                case WindowId::BLOCK_TYPE_WINDOW: window.visible = true;
                case WindowId::BLOCK_PANEL_WINDOW: window.visible = true;
                
                default: break;
            }
        }
    }
    else {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::CODING_WINDOW: {
                    window.x = 10;
                    window.width = GetScreenWidth() - Global::game_window_width - (window.x + 20);
                    Global::coding_window_width = window.width;
                    Global::coding_window_x = window.x;
                }
                break;

                case WindowId::BLOCK_TYPE_WINDOW: window.visible = false;
                case WindowId::BLOCK_PANEL_WINDOW: window.visible = false;

                default: break;
            }
        }
    }
    Global::button_pressed = 0;
}

void Engine::SpritesOffsets()
{
    std::vector<Sprite> new_sprites;
    uint16_t fixed_x_offset;
    uint16_t fixed_y_offset;
    Global::sprites_amount = 0;

    if(window_scale_mode == WindowScaleModes::SMALLER_WINDOW_MODE)
        NewSprite(new_sprites, sprites.size(), 10, 3, false);
    else
        NewSprite(new_sprites, sprites.size(), 20, 5, false);

    sprites = new_sprites;
}

void Engine::CodeCategoryOffsets()
{
    if(Global::current_category != WindowCategory::CATEGORY_CODE) {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::CODING_WINDOW:       window.visible = true; break;
                case WindowId::BLOCK_TYPE_WINDOW:   window.visible = code_panels_mode; break;
                case WindowId::BLOCK_PANEL_WINDOW:  window.visible = code_panels_mode; break;

                case WindowId::ASSETS_WINDOW:       window.visible = false; break;
                default: break;
            }
        }
        buttons[ButtonTrigger::BLOCK_PANELS-1].visible = true;
        Global::current_category = WindowCategory::CATEGORY_CODE;
    }
    Global::button_pressed = 0;
}

void Engine::AssetsCategoryOffsets()
{
    if(Global::current_category != WindowCategory::CATEGORY_ASSETS) {
        for(Window &window: windows) {
            switch(window.id)
            {
                case WindowId::CODING_WINDOW:       window.visible = false; break;
                case WindowId::BLOCK_TYPE_WINDOW:   window.visible = false; break;
                case WindowId::BLOCK_PANEL_WINDOW:  window.visible = false; break;

                case WindowId::ASSETS_WINDOW:       window.visible = true; break;
                default: break;
            }
        }
        buttons[ButtonTrigger::BLOCK_PANELS-1].visible = false;
        Global::current_category = WindowCategory::CATEGORY_ASSETS;
    }
    Global::button_pressed = 0;
}