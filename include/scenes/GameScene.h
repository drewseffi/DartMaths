#pragma once

#include <vector>

#include "scenes/IScene.h"

#include "core/Dartboard.h"

#include "ui/Textbox.h"

class GameScene : public IScene
{
    public:
        GameScene(SceneManager& manager);

        void Update(float dt) override;
        void Draw() override;

    private:
        Dartboard dartboard;
        std::vector<Vector2> hits;
        std::vector<int> scores;

        Textbox textbox;
};