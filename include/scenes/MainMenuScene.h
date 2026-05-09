#pragma once

#include "scenes/IScene.h"

#include "ui/Button.h"

#include "raylib.h"

class MainMenuScene : public IScene
{
    public:
        MainMenuScene(SceneManager& SceneManager);
        ~MainMenuScene();

        void Update(float dt) override;
        void Draw() override;

    private:
        Texture2D logo;
        Button playButton;
        Button quitButton;
};