#include "include/PanelBlocks.hpp"


// PUBLIC
PanelBlocks::PanelBlocks(Block *block)
{
    block_data = block;
    new_dragged_block_id = 0;

    blocks.emplace_back(10, 10, Global::code_panel_scale, Block::Type::PANEL_BLOCK, "Testing One", 1);
    blocks.emplace_back(10, 50, Global::code_panel_scale, Block::Type::PANEL_BLOCK, "Testing Two", 2);
}

void PanelBlocks::Draw(uint16_t window_x, uint16_t window_y)
{
    if(this->window_x != window_x || this->window_y != window_y) {
        this->window_x = window_x;
        this->window_y = window_y;
    }

    for(Block &block: blocks) {
        block.Draw(window_x, window_y);
    }
}

void PanelBlocks::Update()
{
    for(Block &block: blocks) {
        block.Update();
    }

    if(new_dragged_block_id != Global::selected_panel_block && Global::selected_panel_block != 0) {
        new_dragged_block_id = Global::selected_panel_block;
        block_data->text = blocks[Global::selected_panel_block-1].text;
        block_data->offset_x = GetMouseX() - (blocks[Global::selected_panel_block-1].x + window_x);
        block_data->offset_y = GetMouseY() - (blocks[Global::selected_panel_block-1].y + window_y);
        block_data->Data();
    }
}