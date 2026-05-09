#pragma once

#include "managers/SceneManager.h"

class Game
{
    public: 
        Game();
        ~Game();

        void Run();

    private:
        void Initialize();
        void Update(float dt);
        void Draw();
        void Shutdown();

        bool running;
        SceneManager sceneManager;
};