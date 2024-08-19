#include "include/Window.hpp"

Window::Window(uint16_t x, uint16_t y, uint16_t width, uint16_t height) : x(x), y(y), width(width), height(height) {}

void Window::Draw(const std::function<void()>& Render)
{
    Render();
}

void Window::Update()
{

}