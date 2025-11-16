#pragma once // To include the library only once
#include "laser.hpp"
#include <raylib.h> // To render Graphics in this file
#include <vector>

float spaceship_fire_delay = 0.35;
double spaceship_last_fired_time;
int spaceship_laser_count = 0;
const int SPACESHIP_MAX_LASER_COUNT = 100;

Texture2D spaceship_image;
Vector2 spaceship_position; // Position of Spaceship
// std::vector<Laser> spaceship_lasers;
Laser spaceship_lasers[100];
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
  // To free up the memory by unloading the player sprite
  UnloadTexture(spaceship_image); 
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
    // spaceship_lasers.push_back(
    //     Laser({spaceship_position.x + spaceship_image.width / 2 - 4,
    //            spaceship_position.y},
    //           -6));
    std::cout << "[Spaceship] Firing laser....  " << spaceship_laser_count << std::endl;
    spaceship_lasers[spaceship_laser_count] = Laser({spaceship_position.x + spaceship_image.width / 2 - 4,
                                                     spaceship_position.y},
                                                    -6);
    spaceship_laser_count += 1;
    spaceship_last_fired_time = GetTime();
    // std::cout << "[Spaceship] Playing laser sound...." << std::endl;
    PlaySound(spaceship_lasers_sound);
  }
}

Rectangle spaceship_get_rect()
{
  return {spaceship_position.x, spaceship_position.y,
          float(spaceship_image.width), float(spaceship_image.height)};
}

void spaceship_lasers_clear() {
  for(int i = 0; i <= SPACESHIP_MAX_LASER_COUNT - 1; i++) {
    spaceship_lasers[i] = Laser();
  }
}

void spaceship_reset()
{
  spaceship_position.x = (GetScreenWidth() - spaceship_image.width) / 2.0f;
  spaceship_position.y = (GetScreenHeight() - spaceship_image.height);
  spaceship_lasers_clear();
}
