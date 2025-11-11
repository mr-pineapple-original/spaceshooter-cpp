#pragma once // To only call it once
#include<raylib.h>
struct Enemy
{
    Texture2D image;
    Vector2 position;
    int type;
  Enemy(Vector2 i_position, int i_type) 
  {
    position = i_position;
    type = i_type;
    switch (type)
    {
      case 1:
            image = LoadTexture("sprites/enemy-1.png");
            break;
      case 2:
            image = LoadTexture("sprites/enemy-1.png");
            break;
      case 3:
            image = LoadTexture("sprites/enemy-1.png");
            break;
      default:
            image = LoadTexture("sprites/enemy-1.png");
            break;            
    }
  }
  int get_type()
  {
    return type;
  }
    void draw()
    {
      DrawTextureV(image, position, WHITE);
    }
    void update()
    {

    }
};