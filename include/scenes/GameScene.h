#pragma once

#include "scenes/IScene.h"

class GameScene : public IScene
{
public:
    GameScene(SceneManager& manager);

    void Update(float dt) override;
    void Draw() override;
};