#include "include/BlockTypePanel.hpp"


// PUBLIC
BlockTypePanel::BlockTypePanel()
{
    block_types.emplace_back(30, 30, Color{ 177, 62, 83, 255 }, "Testing");
}

void BlockTypePanel::Draw(uint16_t window_x, uint16_t window_y)
{
    for(TypeBlock &block: block_types) {
        block.Draw(window_x, window_y);
    }
}

void BlockTypePanel::Update()
{

}