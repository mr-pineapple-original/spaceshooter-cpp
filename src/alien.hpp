#pragma once
#include <raylib.h>

static float aliens_speed = 1.0f;
struct Alien {
  static Texture2D image[3];
  int type;
  Vector2 position;
  bool active;
  Alien() {
    active = false;
    type = 1;
    position = {-100, -100};
  }
  Alien(int i_type, Vector2 i_position) {
    position = i_position;
    type = i_type;
    active = true;

    if (image[type - 1].id == 0) // To only load the enemy aliens from the
                                 // memory if they haven't been loaded already
    {
      switch (type) {
      case 1:
        image[0] = LoadTexture("sprites/alien-1.png");
        break;
      case 2:
        image[1] = LoadTexture("sprites/alien-2.png");
        break;
      case 3:
        image[2] = LoadTexture("sprites/alien-3.png");
        break;
      default:
        image[0] = LoadTexture("sprites/alien-1.png");
        break;
      }
    }
    // switch (type)
    // {
    //   case 1:
    //     image = LoadTexture("sprites/alien-1.png");
    //     break;
    //   case 2:
    //     image = LoadTexture("sprites/alien-2.png");
    //     break;
    //   case 3:
    //     image = LoadTexture("sprites/alien-3.png");
    //     break;
    //   default:
    //     image = LoadTexture("sprites/alien-1.png");
    //     break;
    // }
  }

  void uninitalize() {
    for (int i = 0; i != 4; i++) {
      UnloadTexture(image[i]); // To unload all the types of the aliens
    }
  }

  void update(int alien_direction) {
    if (!active) {
      return;
    }
    position.x = position.x + alien_direction * aliens_speed;
  }

  // Draw the spaceship from the spaceship header file
  void draw() {
    if (!active) {
      return;
    }
    DrawTextureV(image[type - 1], position, WHITE);
  }

  int get_type() { return type; }

  Rectangle get_rect() {
    if (!active) {
      return {0, 0, 0, 0};
    }

    return {position.x, position.y, float(image[type - 1].width),
            float(image[type - 1].height)};
  }
};
