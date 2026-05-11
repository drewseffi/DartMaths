#include "core/Dartboard.h"

Dartboard::Dartboard(Vector2 center, float radius)
{
    Dartboard::center = center;
    Dartboard::radius = radius;
}

void Dartboard::Draw()
{
    DrawSectors();
    DrawBullseye();
    DrawNumbers();
}

Vector2 Dartboard::GenerateHit()
{

}

void Dartboard::DrawSectors()
{
    for (int i = 0; i < 20; i++)
    {
        float startAngle = i * 18.0f + 9.0f;
        float endAngle = startAngle + 18.0f;

        //--Draw normal scoring sectors
        Color sectorColor = (i % 2 == 0) ? BLACK : BEIGE;

        DrawRing(center, 0.0f, radius, startAngle, endAngle, 32, sectorColor);

        //--Draw double and treble sectors
        Color ringColor = (i % 2 == 0) ? RED : GREEN;

        DrawRing(center, (radius / 2) - 10, (radius / 2) + 10, startAngle, endAngle, 32, ringColor);
        DrawRing(center, radius - 20.0f, radius, startAngle, endAngle, 32, ringColor);
    }
}

void Dartboard::DrawBullseye()
{
    DrawCircle(center.x, center.y, 30.0f, GREEN);
    DrawCircle(center.x, center.y, 15.0f, RED);
}

void Dartboard::DrawNumbers()
{

}