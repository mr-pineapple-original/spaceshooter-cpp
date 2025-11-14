#pragma once // To open this library only once
#include "alien.hpp"
#include "obstacle.hpp"  // To include the obstacle file's struct
#include "spaceship.hpp" // To include spaceship file's functions

std::vector<Obstacle>
    obstacles; // A universial vector variable to store obstacles so we can
               // store it and use it in game_initialize function
std::vector<Alien> aliens;


// To avoid cross referencing we put the create obstacle function in the game header file
std::vector<Obstacle> obstacle_create()
{
    int obstacle_width = Obstacle({100, 100}).grid[0].size() * 3;
    float obstacle_gap = (GetScreenWidth() - (4 * obstacle_width))/5.0f; // Takes the gap between two obstacles by taking the width of all the 4 obstacles and subtracting it from the screen width and dividing it by 5 cause for 4 obstacles you have to add 5 gaps ( 3 for each other and 2 for the parameters of the screen )
    for( int i = 0; i!=4; i++ ) // Running it exactly 4 times to create 4 objects and later draw them
    {
        float obstacle_position_x = (i + 1) * obstacle_gap + i * obstacle_width; // To calculate the x position of the obstacle by ensuring they are evenly spaced
        float obstacle_position_y = GetScreenHeight()-100;
        obstacles.push_back(Obstacle({obstacle_position_x, obstacle_position_y}));
    } 
    return obstacles;
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
    for(auto& obstacle : obstacles)
    {
        obstacle.draw();
    }
    for(auto& alien : aliens)
    {
      alien.draw();
    }

}

std::vector<Alien> create_aliens() {
  std::vector<Alien> temp_aliens;
  for (int row = 0; row < 5; row++) {
    for (int column = 0; column < 11; column++) {

      int alien_type = 1;

      if (row > 3) {
        alien_type = 3;
      } else if (row > 1) {
        alien_type = 2;
      }
      float x = column * 55;
      float y = row * 55;
      temp_aliens.push_back(Alien(alien_type, {x + 75, y + 110}));
    }
  }
  return temp_aliens;
}
void game_initialize() {
  spaceship_initialize();
  obstacles = obstacle_create();
  aliens = create_aliens();
}





// To avoid cross referencing we put the delete laser function in the game
// header file
void delete_laser() {
  for (auto laser = spaceship_lasers.begin();
       laser != spaceship_lasers.end();) {
    if (!laser->active) {
      laser = spaceship_lasers.erase(laser);
    } else {
      ++laser;
    }
  }
}

void game_update() {
  spaceship_boundaries();

  for (auto &laser : spaceship_lasers) {
    laser.update();
  }
  delete_laser();

  for (auto &obstacle : obstacles) {
    obstacle.draw();
  }
}

void handle_input() {
  if (IsKeyDown(KEY_LEFT)) {
    spaceship_position.x = spaceship_position.x - 5;
  } else if (IsKeyDown(KEY_RIGHT)) {
    spaceship_position.x = spaceship_position.x + 5;
  }
  if (IsKeyDown(KEY_SPACE)) {
    spaceship_fire_laser();
  }

  if (IsKeyDown(KEY_Q)) {
    CloseWindow();
  }
}
