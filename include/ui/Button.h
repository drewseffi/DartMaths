#pragma once

#include "raylib.h"
#include <functional>
#include <string>

class Button
{
    public:
        Button(Rectangle rect, std::string text);

        void Update();
        void Draw();

        bool WasClicked() const;

        void SetOnClick(std::function<void()> callback);

    private:
        Rectangle bounds;
        std::string label;

        bool hovered;
        bool pressed;
        bool clicked;

        std::function<void()> onClick;
};