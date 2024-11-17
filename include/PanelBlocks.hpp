#pragma once
#include "CodeBlock.hpp"

class PanelBlocks
{
    private:
        std::vector<std::vector<Block>> blocks;

        uint16_t new_dragged_block_id;
        uint16_t window_x;
        uint16_t window_y;
        
        void Data();

    public:
        Block *block_data;

        PanelBlocks(Block *block);
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
        void Free();
};