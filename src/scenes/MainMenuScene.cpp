#include "scenes/MainMenuScene.h"
#include "scenes/GameScene.h"

#include "managers/SceneManager.h"

#include "ui/Button.h"

#include "raylib.h"


MainMenuScene::MainMenuScene(SceneManager& sceneManager) : IScene(sceneManager), playButton({ 300, 370, 200, 60 }, "PLAY"), quitButton({ 300, 450, 200, 60 }, "QUIT")
{
    logo = LoadTexture("assets/textures/logo.png");
        playButton.SetOnClick([&sceneManager]()
        {
            sceneManager.ChangeScene(
                std::make_unique<GameScene>(sceneManager)
            );
        });

        quitButton.SetOnClick([]()
        {
            CloseWindow();
        });
}

MainMenuScene::~MainMenuScene()
{
    UnloadTexture(logo);
}

void MainMenuScene::Update(float dt)
{
    playButton.Update();
    quitButton.Update();
}

void MainMenuScene::Draw()
{
    DrawTexture(logo, (800 - 650) / 2, ((800 - 650) / 2) - 150, WHITE);

    playButton.Draw();
    quitButton.Draw();
}