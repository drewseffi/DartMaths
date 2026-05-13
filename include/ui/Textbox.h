#pragma once

#include "raylib.h"
#include <string>

enum class AlignHorizontal
{
    LEFT,
    CENTER,
    RIGHT
};

enum class AlignVertical
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
        void TextAlign(AlignHorizontal h, AlignVertical v);
        void BoxOrigin(AlignHorizontal h, AlignVertical v);
        void FontSize(int size);

        std::string GetValue();

        bool selected;
        bool scalable;
        bool inputReceived;

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

        AlignHorizontal textAlign;

        void CalculateTextPos();
        void CalculateBoxPos();
        
        bool StringWillOverflow(std::string s);
        bool ValidInput(std::string s);

        int fontSize;
        int padding;

        bool showingPlaceholder;

        Color boxColor;
        Color textColor;
};