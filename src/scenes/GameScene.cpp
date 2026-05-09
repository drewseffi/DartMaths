#include "scenes/GameScene.h"

#include "managers/SceneManager.h"
#include "scenes/MainMenuScene.h"

#include "raylib.h"

GameScene::GameScene(SceneManager& manager): IScene(manager)
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
    DrawText("GAME SCENE", 400, 200, 40, WHITE);

    DrawText("PRESS ESC TO RETURN", 350, 300, 20, LIGHTGRAY);
}