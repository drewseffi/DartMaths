#include "managers/SceneManager.h"

#include "scenes/IScene.h"

void SceneManager::ChangeScene(std::unique_ptr<IScene> newScene)
{
    currentScene = std::move(newScene);
}

void SceneManager::Update(float dt)
{
    if (currentScene)
    {
        currentScene->Update(dt);
    }
}

void SceneManager::Draw()
{
    if (currentScene)
    {
        currentScene->Draw();
    }
}