#include "core/Game.h"
#include "raylib.h"
#include "scenes/MainMenuScene.h"

Game::Game() : running(false)
{

}

Game::~Game()
{
    Shutdown();
}

void Game::Run()
{
    Initialize();

    running = true;

    while (running && !WindowShouldClose())
    {
        float dt = GetFrameTime();

        Update(dt);
        Draw();
    }
}

void Game::Initialize()
{
    InitWindow(800, 800, "DartMaths");

    SetExitKey(KEY_NULL);

    SetTargetFPS(60);

    sceneManager.ChangeScene(std::make_unique<MainMenuScene>(sceneManager));
}

void Game::Update(float dt)
{
    sceneManager.Update(dt);
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(DARKGREEN);
    sceneManager.Draw();
    EndDrawing();
}

void Game::Shutdown()
{
    CloseWindow();
}