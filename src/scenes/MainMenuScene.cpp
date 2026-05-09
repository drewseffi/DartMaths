#include "scenes/MainMenuScene.h"
#include "scenes/GameScene.h"

#include "managers/SceneManager.h"

#include "raylib.h"

MainMenuScene::MainMenuScene(SceneManager& sceneManager) : IScene(sceneManager)
{

}

void MainMenuScene::Update(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        sceneManager.ChangeScene(std::make_unique<GameScene>(sceneManager));
    }
}

void MainMenuScene::Draw()
{
    DrawText("DART TRAINER", 450, 200, 40, WHITE);

    DrawText("PRESS ENTER TO PLAY", 420, 300, 20, LIGHTGRAY);
}