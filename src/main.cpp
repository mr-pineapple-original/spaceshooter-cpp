// Normal Libraries
#include<iostream>
#include<vector>
#include<math.h>
// Raylib Libraries
#include<raylib.h>
// My Libraries
#include"game.hpp"
#include"spaceship.hpp"
// Using namespace
using namespace std;

int main(void)
{
    // Setting the window
    const int screen_width = 750;
    const int screen_height = 700;
    InitWindow(screen_width, screen_height, "Space Shooters");
    SetTargetFPS(60);
    game_initialize(); // Call function game
    while (!WindowShouldClose()) // When game is opened
    {
        BeginDrawing();
            ClearBackground(BLACK);
            game_draw();
            DrawText("Congrats! You created your first window!", 0 , 0, 20, GRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}