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
    //
    for(auto& laser: spaceship_lasers)
    {
        laser.draw();
    }
}
void game_update()
{
    spaceship_boundaries();

    for(auto& laser: spaceship_lasers) 
    {
        laser.update();
    }
}
void handle_input()
{
    if(IsKeyDown(KEY_LEFT))
    {
        spaceship_position.x = spaceship_position.x - 5;
    }
    else if(IsKeyDown(KEY_RIGHT))
    {
        spaceship_position.x = spaceship_position.x + 5;
    }
    else if(IsKeyDown(KEY_SPACE)) 
    {
        spaceship_fire_laser();
    }
}
