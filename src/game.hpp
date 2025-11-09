#pragma once // To open this library only once
#include"spaceship.hpp" // To include spaceship file's functions
void game_initialize()
{
    spaceship_initialize();
    
}
void game_uninitialize()
{
    
}
void game_draw()
{
    spaceship_draw(); // Draw the spaceship from the spaceship header file
}
void game_update()
{
    spaceship_boundaries();
}
void handle_input()
{
    if(IsKeyDown(KEY_LEFT))
    {
        spaceship_position.x = spaceship_position.x - 5;
    }
    if(IsKeyDown(KEY_RIGHT))
    {
        spaceship_position.x = spaceship_position.x + 5;
    }
}