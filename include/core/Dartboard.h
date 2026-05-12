#pragma once

#include "raylib.h"
#include <vector>

class Dartboard
{
    public:
        Dartboard(Vector2 center, float radius);
        void Draw();
        Vector2 GenerateHit();
        int GenerateScore(Vector2 hitPos);

        std::vector<Vector2> GenerateAllSectors();

    private:
        void InitialiseSectors();

        void DrawSectors();
        void DrawBullseye();
        void DrawNumbers();

        Vector2 center;
        float radius;

        float bullRadius;
        float outerBullRadius;
        float trebleRingInner;
        float trebleRingOuter;
        float doubleRingInner;
        float doubleRingOuter;

        struct Sector
        {
            int value;

            float startAngle;
            float endAngle;

            Color baseColor;
            Color ringColor;
        };

        Sector sectors[20];
};