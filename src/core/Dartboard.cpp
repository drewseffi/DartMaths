#include "core/Dartboard.h"

#include <math.h>

#include <stdio.h>

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

        printf("Start: %f\n", sectors[i].startAngle);
        printf("End: %f\n", sectors[i].endAngle);
    }
}

void Dartboard::Draw()
{
    DrawSectors();
    DrawBullseye();
    DrawNumbers();
}

std::vector<Vector2> Dartboard::GenerateAllSectors()
{
    std::vector<Vector2> allSectors;

    for (int i = 0; i < 20; i++)
    {
        Vector2 hit;

        float angle = (sectors[i].startAngle + 1.0f) * DEG2RAD;
        float distance = (radius / 3) * 2;

        hit.x = center.x + cos(angle) * distance;
        hit.y = center.y + sin(angle) * distance;

        allSectors.push_back(hit);
    }

    return allSectors;
}

int Dartboard::GenerateScore(Vector2 hit)
{
    float ex = hit.x - center.x;
    float ey = hit.y - center.y;

    float distance = sqrt(ex * ex + ey * ey);
    float angle = atan2(ey, ex) * RAD2DEG;

    if (angle < -99.0f)
    {
        angle += 360.0f;
    }

    printf("Hit angle: %f\n", angle);

    int multiplier = 1;

    if (distance < bullRadius)
    {
        return 50;
    }
    else if (distance < outerBullRadius)
    {
        return 25;
    }
    else if (distance > trebleRingInner && distance < trebleRingOuter)
    {
        multiplier = 3;
    }
    else if (distance > doubleRingInner && distance < doubleRingOuter)
    {
        multiplier = 2;
    }
    else
    {
        multiplier = 1;
    }

    for (int i = 0; i < 20; i++)
    {
        if (angle >= sectors[i].startAngle && angle < sectors[i].endAngle)
        {
            return sectors[i].value * multiplier;
        }
    }

    return 0;
}

Vector2 Dartboard::GenerateHit()
{
    float u = GetRandomValue(0, 1000) / 1000.0f;
    float angle = GetRandomValue(0, 360) * DEG2RAD;
    float distance = radius * sqrt(u);

    Vector2 hit;

    hit.x = center.x + cos(angle) * distance;
    hit.y = center.y + sin(angle) * distance;

    return hit;
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