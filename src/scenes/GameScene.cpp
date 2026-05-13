#include "scenes/GameScene.h"
#include "scenes/MainMenuScene.h"

#include "managers/SceneManager.h"

#include "raylib.h"
#include <string>

GameScene::GameScene(SceneManager& manager)
    :   IScene(manager), 
        dartboard({400, 400}, 300.0f), 
        spawnInterval(1.0f), 
        timer(0.0f), 
        currentDart(0), 
        total(0),
        textboxWidth(350.0f),
        textboxHeight(32.0f),
        textbox({400, 730, textboxWidth, textboxHeight}, "Please insert your answer", 10)
{
    currentState = GameState::THROWING;
    textbox.BoxOrigin(AlignHorizontal::CENTER, AlignVertical::CENTER);
    textbox.FontSize(24);
    textbox.TextAlign(AlignHorizontal::CENTER, AlignVertical::CENTER);
}

void GameScene::Update(float dt)
{
    switch(currentState)
    {
        case GameState::THROWING:
        {
            timer += dt;
            if (timer >= spawnInterval)
            {
                hits.push_back(dartboard.GenerateHit());
                scores.push_back(dartboard.GenerateScore(hits.back()));
                currentDart++;
                timer = 0;
            }

            if (currentDart == 3)
            {
                currentState = GameState::WAITING_FOR_INPUT;
            }
            break;
        }
        case GameState::WAITING_FOR_INPUT:
        {
            textbox.selected = true;
            if (textbox.inputReceived)
            {
                answer = textbox.GetValue();
                textbox.selected = false;
                currentState = GameState::CHECKING_ANSWER;
            }
            break;
        }
        case GameState::CHECKING_ANSWER:
        {
            for (int i = 0; i < hits.size(); i++)
            {
                total += scores[i];
            }

            if (std::stoi(answer) == total)
            {
                currentState = GameState::WON;
            }
            else
            {
                currentState = GameState::LOST;
            }
            break;
        }
        case GameState::WON:
        {
            printf("You won!\n");
            currentState = GameState::ROUND_END;
            break;
        }
        case GameState::LOST:
        {
            printf("You lost!\n");
            currentState = GameState::ROUND_END;
            break;
        }
        case GameState::ROUND_END:
        {
            printf("Restarting...\n");
            timer = 0;
            currentDart = 0;
            hits.clear();
            scores.clear();
            total = 0;

            textbox.Reset();

            currentState = GameState::THROWING;
            break;
        }
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

    Color highlightColor = WHITE;
    Color dartColor = ORANGE;

    for (int i = 0; i < hits.size(); i++)
    {
        DrawCircle(hits[i].x, hits[i].y, 5.0f, highlightColor);
        DrawCircle(hits[i].x, hits[i].y, 4.0f, dartColor);
    }

    textbox.Draw();
}