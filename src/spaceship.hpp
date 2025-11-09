#pragma once // To include the library only once
#include<raylib.h> // To render Graphics in this file
Texture2D spaceship_image;
Vector2 spaceship_position; // Position of Spaceship
void spaceship_initialize()
{
    spaceship_image = LoadTexture("sprites/player.png"); // Load the image and assing it to the image attribute
    spaceship_position.x = (GetScreenWidth()-spaceship_image.width)/2;
    spaceship_position.y = GetScreenHeight()-spaceship_image.height; 
}
void spaceship_uninitialize()
{
    UnloadTexture(spaceship_image); // To free up the memory by unloading the player sprite
}
void spaceship_draw()
{
    DrawTextureV(spaceship_image, spaceship_position, WHITE);
}
void spaceship_boundaries()
{
    if(spaceship_position.x<=0)
    {
        spaceship_position.x=10;
    }
    if(spaceship_position.x>=730)
    {
        spaceship_position.x=720;
    }
}
void spaceship_fire_laser();
