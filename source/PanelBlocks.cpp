#include "include/PanelBlocks.hpp"

PanelBlocks::PanelBlocks()
{
    blocks.emplace_back(10, 10, 3.0f, Block::Type::PANEL_BLOCK, "Testing");
}

void PanelBlocks::Draw(uint16_t window_x, uint16_t window_y)
{
    for(Block &block: blocks) {
        block.Draw(window_x, window_y);
    }
}

void PanelBlocks::Update()
{

}