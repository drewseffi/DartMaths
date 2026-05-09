#pragma once

#include <memory>

class IScene;

class SceneManager
{
public:
    void ChangeScene(std::unique_ptr<IScene> newScene);

    void Update(float dt);
    void Draw();

private:
    std::unique_ptr<IScene> currentScene;
};