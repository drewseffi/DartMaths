#include "core/Dartboard.h"

Dartboard::Dartboard(Vector2 center, float radius)
{
    this->center = center;
    this->radius = radius;

    this->bullRadius = 15.0f;
    this->outerBullRadius = 30.0f;

    this->trebleRingInner = (radius / 2) - 10;
    this->trebleRingOuter = (radius / 2) + 10;

    this->doubleRingInner = radius - 20;
    this->doubleRingOuter = radius;

    InitialiseSectors();
}

void Dartboard::InitialiseSectors()
{
    int scores[20] = { 20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5 };

    for (int i = 0; i < 20; i++)
    {
        sectors[i].value = scores[i];

        sectors[i].startAngle = i * 18.0f - 99.0f;
        sectors[i].endAngle = sectors[i].startAngle + 18.0f;

        sectors[i].baseColor = (i % 2 == 0) ? BLACK : BEIGE;
        sectors[i].ringColor = (i % 2 == 0) ? RED : GREEN;
    }
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
        Sector& sector = sectors[i];

        //--Draw sectors
        DrawRing(center, 0.0f, radius, sector.startAngle, sector.endAngle, 32, sector.baseColor);

        //--Draw double and treble sectors
        DrawRing(center, trebleRingInner, trebleRingOuter, sector.startAngle, sector.endAngle, 32, sector.ringColor);
        DrawRing(center, doubleRingInner, doubleRingOuter, sector.startAngle, sector.endAngle, 32, sector.ringColor);
    }
}

void Dartboard::DrawBullseye()
{
    DrawCircle(center.x, center.y, outerBullRadius, GREEN);
    DrawCircle(center.x, center.y, bullRadius, RED);
}

void Dartboard::DrawNumbers()
{

}