#pragma once // To open this library only once
#include "spaceship.hpp" // To include spaceship file's functions
#include "obstacle.hpp" // To include the obstacle file's struct

std::vector<Obstacle> obstacles; // A universial vector variable to store obstacles so we can store it and use it in game_initialize function

// To avoid cross referencing we put the create obstacle function in the game header file
std::vector<Obstacle> obstacle_create()
{
    int obstacle_width = Obstacle({100, 100}).grid[0].size() * 3;
    float obstacle_gap = (GetScreenWidth() - (4 * obstacle_width))/5; // Takes the gap between two obstacles by taking the width of all the 4 obstacles and subtracting it from the screen width and dividing it by 5 cause for 4 obstacles you have to add 5 gaps ( 3 for each other and 2 for the parameters of the screen )
    for( int i = 0; i!=4; i++ ) 
    {
        float obstacle_position_x = (i + 1) * obstacle_gap + i * obstacle_width;
        obstacles.push_back(Obstacle({obstacle_gap, float((GetScreenHeight()-100))}));
    } 
    return obstacles;
}
void game_initialize()
{
    spaceship_initialize();
    obstacles = obstacle_create();
    
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

// To avoid cross referencing we put the delete laser function in the game header file
void delete_laser() 
{
    for(auto laser = spaceship_lasers.begin(); laser != spaceship_lasers.end();)
    {
        if (!laser -> active)
        {
            laser = spaceship_lasers.erase(laser);    
        }
        else 
        {
            ++ laser;
        }
    }
}
void game_update()
{
    spaceship_boundaries();

    for(auto& laser: spaceship_lasers) 
    {
        laser.update();
    }
    delete_laser();

    for(auto& obstacle: obstacles)
    {
        obstacle.draw();
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
    if(IsKeyDown(KEY_SPACE)) 
    {
        spaceship_fire_laser();
    }
}

