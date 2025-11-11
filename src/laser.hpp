#pragma once
#include <raylib.h>
#include <iostream>

struct Laser 
{
  Vector2 position;
  int speed;
  bool active;
  Texture2D image;

  Laser(Vector2 i_position, int i_speed) 
  {
    position = i_position;
    speed = i_speed;
    active=true;
    image = LoadTexture("sprites/player-bullet.png");
  }

  void update()
  {
    position.y += speed;
    if (active)
    {
      if(position.y > GetScreenHeight() || position.y < 0)
      {
        active = false;
        std::cout << "Laser Deleted \n";
      }
    }
  }

  void draw()
  {
    if(active) 
    {
      //DrawRectangle(position.x, position.y, 4, 15, {243,216,63,255});
      DrawTextureV(image, position, WHITE);
    }
  }
};



