#include "ui/Textbox.h"

Textbox::Textbox(Rectangle rect, std::string placeholderText) : bounds(rect), text(placeholderText), selected(true)
{

}

void Textbox::Update()
{
    int key = GetCharPressed();

    while (key > 0)
    {
        text += (char)key;
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {

    }
}

void Textbox::Draw()
{
    Color boxColor = DARKGRAY;
    Color textColor = RED;

    DrawRectangleRec(bounds, boxColor);
    DrawText(text.c_str(), bounds.x, (bounds.y + (bounds.height-MeasureText(text.c_str(), 16)) / 2), 16, textColor);
}

std::string GetValue()
{

}