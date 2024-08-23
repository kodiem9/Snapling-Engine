#include "include/PanelBlocks.hpp"

PanelBlocks::PanelBlocks()
{
    blocks.emplace_back(10, 10, 4.0f, Block::Type::PANEL_BLOCK, "Testing One", 1);
    blocks.emplace_back(10, 50, 4.0f, Block::Type::PANEL_BLOCK, "Testing Two", 2);
}

void PanelBlocks::Draw(uint16_t window_x, uint16_t window_y)
{
    for(Block &block: blocks) {
        block.Draw(window_x, window_y);
    }
}

void PanelBlocks::Update()
{
    for(Block &block: blocks) {
        block.Update();
    }
}