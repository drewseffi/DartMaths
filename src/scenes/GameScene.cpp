#include "scenes/GameScene.h"
#include "scenes/MainMenuScene.h"

#include "managers/SceneManager.h"

#include "raylib.h"

GameScene::GameScene(SceneManager& manager): IScene(manager), dartboard({400, 400}, 300.0f), hits({}), textbox({400, 700}, "Please enter number")
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
        scores.push_back(dartboard.GenerateScore(hits.back()));
        printf("%f", scores.back());
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