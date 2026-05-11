#pragma once

#include "raylib.h"

class Dartboard
{
    public:
        Dartboard(Vector2 center, float radius);
        void Draw();
        Vector2 GenerateHit();
        int GenerateScore(Vector2 hitPos);

    private:
        void DrawSectors();
        void DrawBullseye();
        void DrawNumbers();

        Vector2 center;
        float radius;
};