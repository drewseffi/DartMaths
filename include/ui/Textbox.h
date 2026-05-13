#pragma once

#include "raylib.h"
#include <string>

class Textbox
{
    public:
        Textbox(Rectangle rect, std::string placeholderText);

        void Update();
        void Draw();
        void Reset();

        std::string GetValue();

        bool selected;

    private:
        Rectangle bounds;
        std::string text;
        std::string placeholderText;

        bool showingPlaceholder;

        Color boxColor;
        Color textColor;
};