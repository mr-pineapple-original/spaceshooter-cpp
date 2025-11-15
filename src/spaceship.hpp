#pragma once // To include the library only once
#include "laser.hpp"
#include <raylib.h> // To render Graphics in this file
#include <vector>

float spaceship_fire_delay = 0.35;
double spaceship_last_fired_time;
Texture2D spaceship_image;
Vector2 spaceship_position; // Position of Spaceship
std::vector<Laser> spaceship_lasers;
Sound spaceship_lasers_sound;

void spaceship_initialize()
{
  spaceship_image = LoadTexture("sprites/player.png"); // Load the image and assing it to the
                                         // image attribute
  spaceship_lasers_sound = LoadSound("sounds/player_laser_shoot.wav");
  spaceship_position.x = (GetScreenWidth() - spaceship_image.width) / 2;
  spaceship_position.y = GetScreenHeight() - spaceship_image.height;
}
void spaceship_uninitialize()
{
  UnloadTexture(
      spaceship_image); // To free up the memory by unloading the player sprite
  UnloadSound(spaceship_lasers_sound);
}

void spaceship_draw()
{
  DrawTextureV(spaceship_image, spaceship_position, WHITE);
}
void spaceship_boundaries()
{
  if (spaceship_position.x <= 10)
  {
    spaceship_position.x = 10;
  }
  if (spaceship_position.x >= 730)
  {
    spaceship_position.x = 730;
  }
}
void spaceship_fire_laser()
{
  if (GetTime() - spaceship_last_fired_time >= spaceship_fire_delay)
  {
    spaceship_lasers.push_back(
        Laser({spaceship_position.x + spaceship_image.width / 2 - 4,
               spaceship_position.y},
              -6));
    spaceship_last_fired_time = GetTime();
    PlaySound(spaceship_lasers_sound);
  }
}

Rectangle spaceship_get_rect()
{
  return {spaceship_position.x, spaceship_position.y,
          float(spaceship_image.width), float(spaceship_image.height)};
}

void spaceship_reset()
{
  spaceship_position.x = (GetScreenWidth() - spaceship_image.width) / 2.0f;
  spaceship_position.y = (GetScreenHeight() - spaceship_image.height);
  spaceship_lasers.clear();
}
