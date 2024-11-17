#pragma once
#include "TypeBlock.hpp"

class BlockTypePanel
{
    private:
        std::vector<TypeBlock> block_types;

    public:
        BlockTypePanel();
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};