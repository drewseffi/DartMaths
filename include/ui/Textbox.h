#pragma once

#include "raylib.h"
#include <string>

class Textbox
{
    public:
        Textbox(Rectangle rect, std::string placeholderText);

        void Update();
        void Draw();

        std::string GetValue();

    private:
        Rectangle bounds;
        std::string text;

        bool selected;
};