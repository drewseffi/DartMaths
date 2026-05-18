#include "scenes/GameScene.h"
#include "scenes/MainMenuScene.h"

#include "managers/SceneManager.h"

#include "raylib.h"
#include <string>

GameScene::GameScene(SceneManager& manager)
    :   IScene(manager), 
        dartboard({400, 350}, 300.0f), 
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
    textbox.TextAlign(AlignHorizontal::CENTER, AlignVertical::CENTER);
    textbox.allowSpecialCharacters = false;
    textbox.numerical = true;
    textbox.fontSize = 24;
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
                timer = 0;
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
                if (answer.size() > 3 || std::stoi(answer) > 180 || std::stoi(answer) <= 0)
                {
                    textbox.Reset();
                    textbox.selected = true;
                    answer = textbox.GetValue();
                }
                else
                {
                    textbox.selected = false;
                    currentState = GameState::CHECKING_ANSWER;
                }
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
            timer += dt;

            if (timer >= 2.5f)
            {
                currentState = GameState::ROUND_END;
            }
            break;
        }
        case GameState::LOST:
        {
            timer += dt;

            if (timer >= 2.5f)
            {
                currentState = GameState::ROUND_END;
            }
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

    if (IsKeyPressed(KEY_ESCAPE))
    {
        sceneManager.ChangeScene(std::make_unique<MainMenuScene>(sceneManager));
    }

    textbox.Update();
}

void GameScene::Draw()
{
    if (currentState != GameState::WON || currentState != GameState::LOST)
    {
        dartboard.Draw(); 

        Color highlightColor = WHITE;
        Color dartColor = ORANGE;

        for (int i = 0; i < hits.size(); i++)
        {
            DrawCircle(hits[i].x, hits[i].y, 5.0f, highlightColor);
            DrawCircle(hits[i].x, hits[i].y, 3.0f, dartColor);
        }

        textbox.Draw();
    }

    switch (currentState)
    {
        case GameState::LOST:
        {
            std::string text = "You lost!\nCorrect score was: " + std::to_string(total);
            DrawText(text.c_str(), 400 - MeasureText(text.c_str(), 32) / 2, 350 - 32, 32, WHITE);
            break;
        }

        case GameState::WON:
        {
            DrawText("You won!", 400 - MeasureText("You won!", 32) / 2, 350 - 32, 32, WHITE);
            break;
        }
    }
    
}