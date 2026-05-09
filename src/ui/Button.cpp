#include "ui/Button.h"

#include "raylib.h"

Button::Button(Rectangle rect, std::string text) : bounds(rect), label(text), hovered(false), pressed(false), clicked(false)
{

}

void Button::Update()
{
    Vector2 mouse = GetMousePosition();

    hovered = CheckCollisionPointRec(mouse, bounds);

    clicked = false;

    if (hovered)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            pressed = true;
        }

        if (pressed && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            clicked = true;

            if (onClick)
                onClick();
        }
    }
    else
    {
        pressed = false;
    }
}

void Button::Draw()
{
    Color color = DARKGRAY;

    if (hovered) color = GRAY;
    if (pressed)  color = DARKBLUE;

    DrawRectangleRec(bounds, color);

    int textWidth = MeasureText(label.c_str(), 20);

    DrawText(label.c_str(), bounds.x + (bounds.width - textWidth) / 2, bounds.y + bounds.height / 2 - 10, 20, WHITE);
}

bool Button::WasClicked() const
{
    return clicked;
}

void Button::SetOnClick(std::function<void()> callback)
{
    onClick = callback;
}