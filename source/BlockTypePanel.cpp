#include "include/BlockTypePanel.hpp"


// PUBLIC
BlockTypePanel::BlockTypePanel()
{
    block_types.emplace_back(30, 30, Color{ 177, 62, 83, 255 }, "Testing", 0);
    block_types.emplace_back(150, 30, Color{ 59, 92, 201, 255 }, "Hmmmmm", 1);
}

void BlockTypePanel::Draw(uint16_t window_x, uint16_t window_y)
{
    for(TypeBlock &block: block_types) {
        block.Draw(window_x, window_y);
    }
}

void BlockTypePanel::Update()
{
    for(TypeBlock &block: block_types) {
        block.Update();
    }
}