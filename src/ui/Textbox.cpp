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
        fontSize(16),
        textBounds(bounds),
        textAlign(AlignHorizontal::LEFT),
        inputReceived(false),
        numerical(false),
        allowSpecialCharacters(true)
{
    this->textHorizontal = AlignHorizontal::LEFT;
    this->textVerticle = AlignVertical::TOP;

    this->boxHorizontal = AlignHorizontal::LEFT;
    this->boxVertical = AlignVertical::TOP;
}

void Textbox::Reset()
{
    text = placeholderText;
    showingPlaceholder = true;
    selected = false;
    inputReceived = false;
    CalculateTextPos();
}

void Textbox::Update()
{
    int key = GetCharPressed();

    if(showingPlaceholder)
    {
        CalculateTextPos();
    }

    if (selected)
    {
        boxColor = GRAY;
        textColor = RED;

        if (showingPlaceholder && key > 0)
        {
            text.clear();
            showingPlaceholder = false;
        }
        else if (showingPlaceholder && IsKeyPressed(KEY_BACKSPACE))
        {
            text.clear();
            showingPlaceholder = false;
        }

        while (key > 0)
        {
            std::string textBuffer = text + (char)key;

            if (!StringWillOverflow(textBuffer))
            {
                text += (char)key;
                Textbox::CalculateTextPos();
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && text.size() > 0)
        {
            text.pop_back();
            Textbox::CalculateTextPos();
        }

        if (IsKeyPressed(KEY_ENTER) && ValidInput(text))
        {
            inputReceived = true;
        }
    }
    else
    {
        boxColor = DARKGRAY;
        textColor = WHITE;
    }

    if (scalable)
    {
        bounds = {bounds.x, bounds.y, (float)MeasureText(text.c_str(), fontSize) + (padding * 2), bounds.height};
    }
}

bool Textbox::ValidInput(std::string s)
{
    std::string allowed;

    if (numerical)
    {
        allowed = "0123456789";
    }
    else if (!allowSpecialCharacters)
    {
        allowed =
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789"
            "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    }
    else
    {
        allowed =
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789 ";
    }

    return s.find_first_not_of(allowed) == std::string::npos;
}

bool Textbox::StringWillOverflow(std::string s)
{
    if (MeasureText(s.c_str(), fontSize) > bounds.width - (padding * 2))
    {
        return true;
    }
    else
    {
        return false;
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

void Textbox::TextAlign(AlignHorizontal h, AlignVertical v)
{
    textHorizontal = h;
    textVerticle = v;
    CalculateTextPos();
}

void Textbox::BoxOrigin(AlignHorizontal h, AlignVertical v)
{
    boxHorizontal = h;
    boxVertical = v;
    CalculateBoxPos();
}

void Textbox::CalculateBoxPos()
{
    switch (boxHorizontal)
    {
        case AlignHorizontal::LEFT:
        {
            bounds.x = startingBounds.x;
            break;
        }
        case AlignHorizontal::CENTER:
        {
            bounds.x = bounds.x - (bounds.width / 2);
            break;
        }
        case AlignHorizontal::RIGHT:
        {
            bounds.x -= bounds.width;
            break;
        }
    }

    switch (boxVertical)
    {
        case AlignVertical::TOP:
        {
            bounds.y = startingBounds.y;
            break;
        }
        case AlignVertical::CENTER:
        {
            bounds.y = bounds.y - (bounds.height / 2);
            break;
        }
        case AlignVertical::BOTTOM:
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
        case AlignHorizontal::LEFT:
        {
            textBounds.x = bounds.x + padding;
            break;
        }
        case AlignHorizontal::CENTER:
        {
            textBounds.x = (bounds.x + bounds.width / 2) - (MeasureText(text.c_str(), fontSize) / 2);
            break;
        }
        case AlignHorizontal::RIGHT:
        {
            textBounds.x = bounds.x + bounds.width - padding - MeasureText(text.c_str(), fontSize);
            break;
        }
    }

    switch (textVerticle)
    {
        case AlignVertical::TOP:
        {
            textBounds.y = bounds.y;
            break;
        }
        case AlignVertical::CENTER:
        {
            textBounds.y = bounds.y + (bounds.height - fontSize) / 2;
            break;
        }
        case AlignVertical::BOTTOM:
        {
            textBounds.y = bounds.y + bounds.height - fontSize;
            break;
        }
    }
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