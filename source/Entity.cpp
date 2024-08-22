#include "include/Entity.hpp"

void Entity::Draw(uint16_t window_x, u_int16_t window_y, uint8_t id)
{
    DrawRectangle(Global::entities[id].x + window_x + Global::game_window_width / 2 - 25, Global::entities[id].y + window_y + Global::game_window_height / 2 - 25, 50, 50, RED);
}

void Entity::Update(uint8_t id)
{
    
}