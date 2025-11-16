#pragma once
#include <iostream>
#include <raylib.h>

struct Laser {
  Vector2 position;
  int speed;
  bool active;
  Texture2D image;

  Laser() {
    speed = 0;
    position = {-100, -100};
  }
  Laser(Vector2 i_position, int i_speed) {
    position = i_position;
    speed = i_speed;
    active = true;
    image = LoadTexture("sprites/player-bullet.png");
  }

  void update() {
    position.y += speed;
    if (active) {
      if (position.y > GetScreenHeight() || position.y < 0) {
        active = false;
        std::cout << "Laser Deleted \n";
      }
    }
  }

  void draw() {
    if (active) {
      // DrawRectangle(position.x, position.y, 4, 15, {243,216,63,255});
      DrawTextureV(image, position, WHITE);
    }
  }

  Rectangle get_rect() {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = float(image.width);
    rect.height = float(image.height);
    return rect;
  }
};
