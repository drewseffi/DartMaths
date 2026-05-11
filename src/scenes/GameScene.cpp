#include "scenes/GameScene.h"

#include "managers/SceneManager.h"
#include "scenes/MainMenuScene.h"

#include "raylib.h"

GameScene::GameScene(SceneManager& manager): IScene(manager), dartboard({400, 400}, 300.0f)
{

}

void GameScene::Update(float dt)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        sceneManager.ChangeScene(std::make_unique<MainMenuScene>(sceneManager));
    }
}

void GameScene::Draw()
{
    dartboard.Draw();
}