#include "ui/Textbox.h"

Textbox::Textbox(Rectangle rect, std::string placeholderText) : bounds(rect), text(placeholderText), selected(false), showingPlaceholder(true), placeholderText(placeholderText)
{

}

void Textbox::Reset()
{
    text = placeholderText;
    showingPlaceholder = true;
    selected = false;
}

void Textbox::Update()
{
    int key = GetCharPressed();

    if (selected)
    {
        boxColor = GRAY;
        textColor = RED;

        if (showingPlaceholder && key > 0)
        {
            text.clear();
            showingPlaceholder = false;
        }

        while (key > 0)
        {
            text += (char)key;
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && text.size() > 0)
        {
            text.pop_back();
        }
    }
    else
    {
        boxColor = DARKGRAY;
        textColor = WHITE;
    }
}

void Textbox::Draw()
{
    DrawRectangleRec(bounds, boxColor);
    float centerY = (bounds.y + (bounds.height) / 2) - 8;
    DrawText(text.c_str(), bounds.x, centerY, 16, textColor);
}

std::string Textbox::GetValue()
{
    return text;
}