#pragma once

#include <vector>
#include <string>

#include "scenes/IScene.h"

#include "core/Dartboard.h"

#include "ui/Textbox.h"

enum class GameState
{
    THROWING,
    WAITING_FOR_INPUT,
    CHECKING_ANSWER,
    WON,
    LOST,
    ROUND_END
};
class GameScene : public IScene
{
    public:
        GameScene(SceneManager& manager);

        void Update(float dt) override;
        void Draw() override;

    private:
        Dartboard dartboard;
        std::vector<Vector2> hits;
        std::vector<int> scores;

        Textbox textbox;

        float spawnInterval;
        float timer;
        int currentDart;
        int total;
        std::string answer;

        GameState currentState;
};