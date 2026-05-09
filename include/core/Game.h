#pragma once

class Game
{
    public: 
        Game();
        ~Game();

        void Run();

    private:
        void Initialize();
        void Update();
        void Draw();
        void Shutdown();

        bool running;
};