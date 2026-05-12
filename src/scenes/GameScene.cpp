#include "scenes/GameScene.h"
#include "scenes/MainMenuScene.h"

#include "managers/SceneManager.h"

#include "raylib.h"
#include <string>

GameScene::GameScene(SceneManager& manager): IScene(manager), dartboard({400, 400}, 300.0f), textbox({400, 700, 200, 32}, "Please enter number")
{

}

void GameScene::Update(float dt)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        sceneManager.ChangeScene(std::make_unique<MainMenuScene>(sceneManager));
    }

    if (IsKeyPressed(KEY_E))
    {
        hits.push_back(dartboard.GenerateHit());
        scores.push_back(dartboard.GenerateScore(hits.back()));

        printf("%i\n", scores.back());
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        std::string result = textbox.GetValue();
        printf("%s\n", result);
    }

    if (IsKeyPressed(KEY_D))
    {
        std::vector<Vector2> test = dartboard.GenerateAllSectors();
        for (int i = 0; i < test.size(); i++)
        {
            printf("%i\n", dartboard.GenerateScore(test[i]));
            hits.push_back(test[i]);
        }
    }

    textbox.Update();
}

void GameScene::Draw()
{
    dartboard.Draw();

    Color dartColor = ORANGE;

    for (int i = 0; i < hits.size(); i++)
    {
        if (i % 2 == 0) 
        {
            dartColor = SKYBLUE;
        }
        else 
        {
            dartColor = ORANGE;
        }
    
        DrawCircle(hits[i].x, hits[i].y, 5.0f, dartColor);
    }

    textbox.Draw();
}