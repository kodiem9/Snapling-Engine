#include <BlockTypePanel.hpp>

// PUBLIC
BlockTypePanel::BlockTypePanel()
{
    block_types.emplace_back(Color{ 177, 62, 83, 255 }, "Testing");
    block_types.emplace_back(Color{ 59, 92, 201, 255 }, "Hmmmmm");
    block_types.emplace_back(Color{ 56, 183, 100, 255 }, "GREEN");
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