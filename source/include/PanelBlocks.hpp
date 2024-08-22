#pragma once
#include "Global.hpp"
#include "CodeBlock.hpp"

class PanelBlocks
{
    private:
        std::vector<Block> blocks;

    public:
        PanelBlocks();
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};