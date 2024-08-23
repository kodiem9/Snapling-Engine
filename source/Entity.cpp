#include "include/Entity.hpp"

void Entity::Draw(uint16_t window_x, u_int16_t window_y, uint8_t id)
{
    uint16_t entity_size = 64 * ((float)Global::game_scale / 10);
    DrawRectangle(Global::entities[id].x + window_x + Global::game_window_width / 2 - entity_size / 2, Global::entities[id].y * -1 + window_y + Global::game_window_height / 2 - entity_size / 2, entity_size, entity_size, RED);}

void Entity::Update(uint8_t id)
{
    
}