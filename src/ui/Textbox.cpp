#include "ui/Textbox.h"

Textbox::Textbox(Rectangle rect, std::string placeholderText, int stringPadding)
    :   bounds(rect), 
        text(placeholderText), 
        selected(false), 
        showingPlaceholder(true), 
        placeholderText(placeholderText), 
        padding(stringPadding),
        scalable(false),
        startingBounds(rect),
        fontSize(16)
{
    this->textHorizontal = LEFT;
    this->textVerticle = TOP;

    this->boxHorizontal = LEFT;
    this->boxVertical = TOP;

    this->textBounds = bounds;
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

    if (scalable)
    {
        bounds = {bounds.x, bounds.y, (float)MeasureText(text.c_str(), 24) + (padding * 2), bounds.height};
    }
}

void Textbox::Resize(float w, float h)
{
    bounds = {bounds.x, bounds.y, w, h};
}

void Textbox::Reposition(float x, float y)
{
    bounds = {x, y, bounds.width, bounds.height};
}

void Textbox::AlignText(AlignHorizontal h, AlignVertical v)
{
    textHorizontal = h;
    textVerticle = v;
    CalculateTextPos();
}

void Textbox::AlignBox(AlignHorizontal h, AlignVertical v)
{
    boxHorizontal = h;
    boxVertical = v;
    CalculateBoxPos();
}

void Textbox::CalculateBoxPos()
{
    switch (boxHorizontal)
    {
        case LEFT:
        {
            bounds.x = startingBounds.x;
            break;
        }
        case MIDDLE:
        {
            bounds.x = bounds.x - (bounds.width / 2);
            break;
        }
        case RIGHT:
        {
            bounds.x -= bounds.width;
            break;
        }
    }

    switch (boxVertical)
    {
        case TOP:
        {
            bounds.y = startingBounds.y;
            break;
        }
        case CENTER:
        {
            bounds.y = bounds.y - (bounds.height / 2);
            break;
        }
        case BOTTOM:
        {
            bounds.y -= bounds.height;
            break;
        }
    }
}

void Textbox::CalculateTextPos()
{
    switch (textHorizontal)
    {
        case LEFT:
        {
            textBounds.x = bounds.x + padding;
            break;
        }
        case MIDDLE:
        {
            textBounds.x = bounds.x + (MeasureText(text.c_str(), fontSize) / 2);
            break;
        }
        case RIGHT:
        {
            textBounds.x = bounds.x + bounds.width - padding;
            break;
        }
    }

    switch (textVerticle)
    {
        case TOP:
        {
            textBounds.y = bounds.y;
            break;
        }
        case CENTER:
        {
            textBounds.y = bounds.y + (bounds.height - fontSize) / 2;
            break;
        }
        case BOTTOM:
        {
            textBounds.y = bounds.y + bounds.height - fontSize;
            break;
        }
    }
}

void Textbox::FontSize(int size)
{
    fontSize = size;
}

void Textbox::Draw()
{
    DrawRectangleRec(bounds, boxColor);
    DrawText(text.c_str(), textBounds.x, textBounds.y, fontSize, textColor);
}

std::string Textbox::GetValue()
{
    return text;
}