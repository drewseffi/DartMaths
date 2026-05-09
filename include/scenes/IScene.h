#pragma once

class SceneManager;

class IScene
{
    public:
        IScene(SceneManager& manager);
        virtual ~IScene() = default;

        virtual void Update(float dt) = 0;
        virtual void Draw() = 0;

    protected:
    SceneManager& sceneManager;
};