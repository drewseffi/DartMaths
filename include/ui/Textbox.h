#pragma once

#include "raylib.h"
#include <string>

enum AlignHorizontal
{
    LEFT,
    MIDDLE,
    RIGHT
};

enum AlignVertical
{
    TOP,
    CENTER,
    BOTTOM
};

class Textbox
{
    public:
        Textbox(Rectangle rect, std::string placeholderText, int stringPadding);

        void Update();
        void Draw();
        void Reset();
        void Resize(float width, float height);
        void Reposition(float x, float y);
        void AlignText(AlignHorizontal h, AlignVertical v);
        void AlignBox(AlignHorizontal h, AlignVertical v);
        void FontSize(int size);

        std::string GetValue();

        bool selected;
        bool scalable;

    private:
        Rectangle bounds;
        Rectangle startingBounds;
        Rectangle textBounds;

        std::string text;
        std::string placeholderText;

        AlignHorizontal textHorizontal;
        AlignVertical textVerticle;

        AlignHorizontal boxHorizontal;
        AlignVertical boxVertical;

        void CalculateTextPos();
        void CalculateBoxPos();

        int fontSize;
        int padding;

        bool showingPlaceholder;

        Color boxColor;
        Color textColor;
};