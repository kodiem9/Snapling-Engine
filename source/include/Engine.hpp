#pragma once
#include "Window.hpp"
#include "PopUp.hpp"
#include "Sprite.hpp"
#include "PropertiesBox.hpp"
#include "Entity.hpp"
// PanelBlocks.hpp HAS CodeBlocks.hpp INSIDE
#include "PanelBlocks.hpp"
#include "Grid.hpp"
// BlockTypePanel.hpp HAS BlockType.hpp INSIDE
#include "BlockTypePanel.hpp"
// BlockTypePanel.hpp HAS Button.hpp INSIDE
#include "Category.hpp"
#include "Costume.hpp"

enum ButtonTrigger
{
    FULLSCREEN = 1,
    BIGGER_WINDOW,
    SMALLER_WINDOW,
    NEW_SPRITE,
    EMPTY_SPRITE,
    BLOCK_PANELS,
    CODE_CATEGORY,
    ASSETS_CATEGORY,
    COSTUMES_PANEL
};

enum WindowId
{
    GAME_WINDOW,
    PROPERTIES_WINDOW,
    SPRITES_WINDOW,
    CODING_WINDOW,
    BLOCK_TYPE_WINDOW,
    BLOCK_PANEL_WINDOW,
    ASSETS_WINDOW,
    COSTUMES_WINDOW
};

enum WindowScaleModes
{
    FULLSCREEN_MODE,
    BIGGER_WINDOW_MODE,
    SMALLER_WINDOW_MODE
};

enum WindowCategory
{
    CATEGORY_CODE,
    CATEGORY_ASSETS
};

#define WINDOW_OUTLINE_COLOR    Color{ 195, 204, 217, 255 }
#define WINDOWS_UNIQUE_BG_COLOR Color{ 231, 240, 252, 255 }
#define WINDOW_CODE_PANEL_COLOR Color{ 249, 249, 249, 255 }
#define WINDOW_COSTUMES_COLOR   Color{ 217, 227, 242, 255 }

#define POPUP_COLOR             Color{ 177, 62, 83, 180 }

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
        std::vector<Category> categories;
        std::vector<Sprite> sprites;
        std::vector<std::vector<Block>> blocks;
        std::vector<std::vector<Costume>> costumes;
        
        PopUp *new_sprite_popup;
        PropertiesBox *properties_box;
        PanelBlocks *panel_blocks;
        Entity *entity;
        Block *dragged_block;
        Grid *grid;
        BlockTypePanel *block_type_panel;

        float tween_timer;

        uint16_t sprite_window_height;

        uint8_t window_scale_mode;
        uint8_t saved_window_scale_mode;
        bool code_panels_mode;
        bool costumes_panel_mode;

        
        inline void InitData();
        inline void InitWindows();
        inline void InitButtons();
        inline void InitCategories();

        inline void PopUpUpdate();
        inline void NewSprite(std::vector<Sprite> &sprites, uint16_t loop, uint8_t offset, uint8_t row, bool upd_curr_spr);
        inline void SpriteData();
        inline void NewCostume();

        void Commands();
        void ButtonUpdate();
        void FullscreenOffsets();
        void BiggerWindowOffsets();
        void SmallerWindowOffsets();
        void BlockPanelsOffsets();
        void SpritesOffsets();
        void CostumesOffsets();
        void CodeCategoryOffsets();
        void AssetsCategoryOffsets();
};