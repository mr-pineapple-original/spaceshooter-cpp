#pragma once // To only call it once
#include "laser.hpp"
#include <raylib.h>

struct Block
{
  Vector2 position;

  Block(Vector2 i_position) { position = i_position; }

  void draw()
  {
    DrawRectangle(position.x, position.y, 3, 3, {0, 255, 255, 255});
  }

  Rectangle get_rect()
  {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
  }
};
