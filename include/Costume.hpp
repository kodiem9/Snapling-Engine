#pragma once
#include "Global.hpp"

#define COSTUME_BG_COLOR            Color{ 217, 228, 243, 255 }
#define COSTUME_OUTLINE_COLOR       Color{ 184, 193, 205, 255 }
#define COSTUME_SELECTED_OUTLINE_COLOR   Color{ 177, 62, 83, 255 }

constexpr uint8_t COSTUME_SIZE{100};

class Costume
{
    private:
        uint16_t x;
        uint16_t y;
        uint16_t fixed_x{};
        uint16_t fixed_y{};

        uint8_t id;
        
    public:
        Costume(uint8_t id);
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update() const;
};