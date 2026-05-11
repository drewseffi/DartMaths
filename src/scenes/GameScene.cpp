#include "scenes/GameScene.h"

#include "managers/SceneManager.h"
#include "scenes/MainMenuScene.h"

#include "raylib.h"

GameScene::GameScene(SceneManager& manager): IScene(manager), dartboard({400, 400}, 300.0f), hits({})
{

}

void GameScene::Update(float dt)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        sceneManager.ChangeScene(std::make_unique<MainMenuScene>(sceneManager));
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        hits.push_back(dartboard.GenerateHit());
        float score = dartboard.GenerateScore(hits.back());
        printf("%f", score);
    }
}

void GameScene::Draw()
{
    dartboard.Draw();

    for (int i = 0; i < hits.size(); i++)
    {
        DrawCircle(hits[i].x, hits[i].y, 5.0f, ORANGE);
    }
}