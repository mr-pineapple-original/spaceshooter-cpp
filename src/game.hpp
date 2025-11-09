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

}
void handle_input()
{

}