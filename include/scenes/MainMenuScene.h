#pragma once

#include "scenes/IScene.h"

class MainMenuScene : public IScene
{
    public:
        MainMenuScene(SceneManager& SceneManager);

        void Update(float dt) override;
        void Draw() override;
};