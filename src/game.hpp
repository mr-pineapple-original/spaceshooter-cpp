#pragma once // To open this library only once
#include "alien.hpp"
#include "obstacle.hpp"  // To include the obstacle file's struct
#include "spaceship.hpp" // To include spaceship file's functions
#include <fstream>       // To store highscore in a text file so we load the text from it everytime the game is opened
#include <raylib.h>

int alien_direction =
    1; // Global variable to use it in the move_alien function and passing it as
       // an argument to update() function in the alien.hpp file
constexpr static float alien_laser_interval =
    0.35; // Global variable to calculate the laser shooting interval by aliens
float alien_fired_last_time = 0.0;

Obstacle obstacles[5];
// obstacles so we can store it and use it in game_initialize function
Alien aliens[55];
Laser alien_lasers[100];

int spaceship_health = 3;
bool game_run;              // To display the Game Over screen once it becomes false
bool game_is_ended = false; // To end the game after level 5
bool game_is_paused = false;
int game_current_level = 1;
int score; // To display score in the Game
int highscore;

int alien_laser_count = 0;
const int ALIEN_LASER_MAX_COUNT = 100;

Music music;                 // To use this variable to open music file
Sound enemy_death_sound;     // To use this variable to open enemy_death_sound
Sound spaceship_death_sound; // To use this variable to open game_over
Sound spaceship_damage;      // To use this variable to open player_hurt

// To avoid cross referencing we put the create obstacle function in the game
// header file
void create_obstacles()
{

  int obstacle_width = (sizeof(Obstacle::grid[0]) / sizeof(int)) * 3;

  // Takes the gap between two obstacles by taking the width of all
  // the 4 obstacles and subtracting it from the screen width and
  // dividing it by 5 cause for 4 obstacles you have to add 5 gaps ( 3
  // for each other and 2 for the parameters of the screen )
  // game_running it exactly 4 times to create 4
  // objects and later draw them
  float obstacle_gap = (GetScreenWidth() - (4 * obstacle_width)) / 5.0f;
  for (int i = 0; i != 4; i++)
  {
    float obstacle_position_x =
        (i + 1) * obstacle_gap +
        i * obstacle_width; // To calculate the x position of the obstacle by
                            // ensuring they are evenly spaced
    float obstacle_position_y = GetScreenHeight() - 100;

    obstacles[i] = Obstacle({obstacle_position_x, obstacle_position_y});
  }
}

void check_highscore() // To check for highscore
{
  if (score > highscore)
  {
    highscore = score;
  }
}

void save_highscore_in_file(int highscore)
{
  std::ofstream highscore_file("highscore.txt");
  if (highscore_file.is_open())
  {
    highscore_file
        << highscore; // Write the current highscore in the highscore_file file
                      // pointer to update the value in the highscore.txt file
    highscore_file.close();
  }
  else
  {
    std::cerr << "Failed to save highscore to file" << std::endl;
  }
}

void game_end()
{
  std::cout << "Game Completed" << std::endl;
  game_is_ended = true;
  game_run = true;
  save_highscore_in_file(highscore);
}

int load_highscore_from_file()
{
  int loaded_highscore = 0;
  std::ifstream highscore_file("highscore.txt");
  if (highscore_file.is_open())
  {
    highscore_file >> loaded_highscore;
  }
  else
  {
    std::cerr << "Failed to load highscore from file." << std::endl;
  }
  return loaded_highscore;
}

void game_uninitialize()
{
  for (int i = 0; i <= 54; i++)
  {
    aliens[i] = Alien();
    aliens[i].uninitalize();
  }
  UnloadMusicStream(music);
  UnloadSound(enemy_death_sound);
  UnloadSound(spaceship_death_sound);
  UnloadSound(spaceship_damage);
}
void game_draw()
{

  std::string health_text = "Health: " + std::to_string(spaceship_health);
  std::string score_text = "Score: " + std::to_string(score);
  std::string highscore_text = "High-Score: " + std::to_string(highscore);
  std::string level_text =
      "Current Level: " + std::to_string(game_current_level);

  DrawText(health_text.c_str(), 0, 0, 20, RED);
  DrawText(level_text.c_str(), 0, 680, 20, GREEN);

  DrawText(score_text.c_str(), 630, 0, 20, YELLOW);
  DrawText(highscore_text.c_str(), 630 / 2, 0, 20, BLUE);

  if (game_is_paused)
  {
    DrawText("Game Paused", (GetScreenWidth() / 2) - 120,
             (GetScreenHeight() / 2) - 20, 40, LIGHTGRAY);
  }
  if (!game_run)
  {
    ClearBackground(BLACK);

    DrawText("You lose! Press 'Enter' to restart", 15,
             (GetScreenHeight() / 2) - 20, 40, LIGHTGRAY);
  }
  if (game_is_ended)
  {
    ClearBackground(BLACK);

    DrawText("You Win!! Press 'Enter' to restart", 15,
             (GetScreenHeight() / 2) - 20, 40, LIGHTGRAY);
  }

  spaceship_draw(); // Draw the spaceship from the spaceship header file
  //
  for (unsigned int i = 0; i<100; i++)
  {
    spaceship_lasers[i].draw();
  }
  for (unsigned int i = 0; i<5; i++)
  {
    obstacles[i].draw();
  }
  for (unsigned int i = 0; i<55; i++)
  {
    aliens[i].draw();
  }
  for (unsigned int i = 0; i<100; i++)
  {
    alien_lasers[i].draw();
  }
}

void create_aliens()
{
  int i = 0;
  for (int row = 0; row < 5; row++)
  {
    for (int column = 0; column < 11; column++)
    {

      int alien_type = 1;

      if (row == 0)
      {
        alien_type = 3;
      }
      else if (row == 1 || row == 2)
      {
        alien_type = 2;
      }
      float x = column * 55;
      float y = row * 55;
      aliens[i] = Alien(alien_type, {x + 75, y + 110});
      i++;
    }
  }
}

void alien_laser() // To shoot lasers from the aliens
{
  double current_time = GetTime();
  int random_value = GetRandomValue(0, 55 - 1);

  Alien alien = aliens[random_value];
  if (current_time - alien_fired_last_time >= alien_laser_interval &&
      alien.active != false)
  {
    if(alien_laser_count==ALIEN_LASER_MAX_COUNT)
    {
      alien_laser_count--;
    }
    alien_lasers[alien_laser_count] = 
        Laser({alien.position.x + alien.image[alien.type - 1].width / 2,
               alien.position.y + alien.image[alien.type - 1].height},
              6);
    alien_laser_count++;
    alien_fired_last_time = GetTime();
  }
}

void alien_move_down(int distance) // To move the aliens down in the game.hpp file by calling
                  // this function in the alien_move function
{
  for (unsigned int i =0; i<55; i++)
  {
    aliens[i].position.y = aliens[i].position.y + distance;
  }
}

void alien_move() // To move the aliens horizontally in the game.hpp file by
                  // calling a function update() from the alien struct
{
  for (int i =0; i<55; i++)
  {
    if (aliens[i].position.x + aliens[i].image[aliens[i].type - 1].width >
        GetScreenWidth()) // To avoid aliens getting out from the right side of
                          // the window screen
    {
      alien_direction = -1; // We make them move left if they collide from the
                            // right boundary of the screen
      alien_move_down(2);   // To move the alien 4 pixels down
    }
    if (aliens[i].position.x < 0) // To avoid aliens getting out from the left side
                              // of the window screen
    {
      alien_direction = 1; // We make them move right if they collide from the
                           // left boundary of the screen
      alien_move_down(2);
    }
    aliens[i].update(alien_direction);
  }
}

void game_initialize()
{
  score = 0;
  game_current_level = 1;
  aliens_speed = 1;
  spaceship_fire_delay = 0.35;
  highscore = load_highscore_from_file();
  game_run = true;
  spaceship_health = 3;
  music = LoadMusicStream("sounds/music.mp3");
  enemy_death_sound = LoadSound("sounds/enemy_death.mp3");
  spaceship_death_sound = LoadSound("sounds/game_over.wav");
  spaceship_damage = LoadSound("sounds/player_hurt.mp3");
  PlayMusicStream(music);
  spaceship_initialize();
  create_obstacles();
  create_aliens();
}

// To avoid cross referencing we put the delete laser function in the game
// header file
void laser_delete()
{
  // for (auto laser = spaceship_lasers;
  //      laser != SPACESHIP_MAX_LASER_COUNT - 1;)
  // {
  //   if (!laser->active)
  //   {
  //     laser = spaceship_lasers.erase(laser);
  //   }
  //   else
  //   {
  //     ++laser;
  //   }
  // }
  for (int i = 0; i <= SPACESHIP_MAX_LASER_COUNT - 1; i++){
    if (!spaceship_lasers[i].active) {
        spaceship_lasers[i] = Laser();
        spaceship_laser_count--;
      }
  }

  // for (auto laser = alien_lasers.begin(); laser != alien_lasers.end();)
  // {
  //   if (!laser->active)
  //   {
  //     laser = alien_lasers.erase(laser);
  //   }
  //   else
  //   {
  //     ++laser;
  //   }
  // }
  for (int i = 0; i <= ALIEN_LASER_MAX_COUNT - 1; i++){
    if (!alien_lasers[i].active) {
        alien_lasers[i] = Laser();
        alien_laser_count--;
      }
  }
}

void game_over()
{
  std::cout << "Game Over" << std::endl;
  PlaySound(spaceship_death_sound);
  game_run = false;
  save_highscore_in_file(highscore);
}

void game_level_completed()
{
  if (game_current_level == 5)
  {
    game_end();
  }
  else
  {
    std::cout << "Level completed" << endl;
    aliens_speed += 0.3;
    spaceship_fire_delay -= 0.02;
    game_current_level += 1;
    create_aliens();
    create_obstacles();
  }
}

bool aliens_is_empty()
{
  bool flag = true;
  for (int i = 0; i <= 54; i++)
  {
    if (aliens[i].active == true)
    {
      flag = false;
    }
  }
  return flag;
}

void check_for_collisions()
{
  // Spaceship lasers
  for (unsigned int it = 0; it < SPACESHIP_MAX_LASER_COUNT; it++)
  {
    for (int j = 0; j <= 54; j++)
    {
      if (CheckCollisionRecs(aliens[j].get_rect(), spaceship_lasers[it].get_rect()))
      {
        PlaySound(enemy_death_sound);
        if (aliens[j].type == 1)
        {
          score = score + 100;
        }
        if (aliens[j].type == 2)
        {
          score = score + 200;
        }
        if (aliens[j].type == 3)
        {
          score = score + 300;
        }
        check_highscore();
        // Delete the alien.
        aliens[j].active = false;

        spaceship_lasers[it].active = false;
      }
    }

    // for (auto &obstacle : obstacles) {
    //   auto it = obstacle.blocks.begin();
    //   while (it != obstacle.blocks.end()) {
    //     if (CheckCollisionRecs(it->get_rect(), laser.get_rect())) {
    //       it = obstacle.blocks.erase(it);
    //       laser.active = false;
    //     } else {
    //       ++it;
    //     }
    //   }
    // }
    for (int i = 0; i <= 4; i++)
    {
      for (int j = 0; j <= 275; j++)
      {
        if (CheckCollisionRecs(obstacles[i].blocks[j].get_rect(), spaceship_lasers[it].get_rect()))
        {
          obstacles[i].blocks[j] = Block();
          spaceship_lasers[it].active = false;
        }
      }
    }
  }

  if (aliens_is_empty())
  {
    game_level_completed();
  }
  // Alien lasers
  for (unsigned int it = 0; it < ALIEN_LASER_MAX_COUNT; it++)
  {
    if (CheckCollisionRecs(alien_lasers[it].get_rect(), spaceship_get_rect()))
    {
      alien_lasers[it].active = false;
      PlaySound(spaceship_damage);
      spaceship_health -= 1;
      if (spaceship_health == 0)
      {
        game_over();
      }
    }
    // for (auto &obstacle : obstacles)
    // {
    //   auto it = obstacle.blocks.begin();
    //   while (it != obstacle.blocks.end())
    //   {
    //     if (CheckCollisionRecs(it->get_rect(), laser.get_rect()))
    //     {
    //       it = obstacle.blocks.erase(it);
    //       laser.active = false;
    //     }
    //     else
    //     {
    //       ++it;
    //     }
    //   }
    // }
    for (int i = 0; i <= 4; i++)
    {
      for (int j = 0; j <= 275; j++)
      {
        if (CheckCollisionRecs(obstacles[i].blocks[j].get_rect(), alien_lasers[it].get_rect()))
        {
          obstacles[i].blocks[j] = Block();
          alien_lasers[it].active = false;
        }
      }
    }
  }

  // Aliens
  for (int i=0; i<55; i++)
  {
    // for (auto &obstacle : obstacles)
    // {
    //   auto it = obstacle.blocks.begin();
    //   while (it != obstacle.blocks.end())
    //   {
    //     if (CheckCollisionRecs(it->get_rect(), alien.get_rect()))
    //     {
    //       it = obstacle.blocks.erase(it);
    //     }
    //     else
    //     {
    //       ++it;
    //     }
    //   }
    // }
    for (int j = 0; j <= 4; j++)
    {
      for (int k = 0; k <= 275; k++)
      {
        if (CheckCollisionRecs(obstacles[j].blocks[k].get_rect(), aliens[i].get_rect()))
        {
          obstacles[j].blocks[k] = Block();
        }
      }
    }

    if (CheckCollisionRecs(aliens[i].get_rect(), spaceship_get_rect()))
    {
      game_over();
    }
  }
}

void game_update()
{
  if (!game_run)
  {
    return;
  }

  if (game_is_ended)
  {
    return;
  }
  if (game_is_paused)
  {
    return;
  }

  UpdateMusicStream(music);
  spaceship_boundaries();

  for (unsigned int i =0; i < SPACESHIP_MAX_LASER_COUNT; i++)
  {
    spaceship_lasers[i].update();
  }
  laser_delete();

  for (unsigned int i = 0; i < 5; i++)
  {
    obstacles[i].draw();
  }
  alien_laser();
  for (unsigned int i =0; i <  ALIEN_LASER_MAX_COUNT; i++)
  {
    alien_lasers[i].update();
  }
  alien_move();
  check_for_collisions();
}

void aliens_clear()
{
  for (int i = 0; i <= 54; i++)
  {
    aliens[i] = Alien();
  }
}

void alien_lasers_clear() {
  for(int i = 0; i <= ALIEN_LASER_MAX_COUNT - 1; i++) {
    alien_lasers[i] = Laser();
  }
}


void game_reset()
{
  // delete everything
  spaceship_reset();
  aliens_clear();
  alien_lasers_clear();
  // obstacles.clear();

  // bad way to clear obstacles
  for (int i = 0; i < 5; i++)
  {
    obstacles[i] = Obstacle({-100, -100});
  }

  // recreate everything
  game_initialize();
}

void handle_input()
{
  if (game_is_ended)
  {
    if (IsKeyDown(KEY_ENTER))
    {
      save_highscore_in_file(highscore);
      game_is_ended = false;
      game_reset();
    }
  }
  if (!game_run)
  {
    if (IsKeyDown(KEY_ENTER))
    {
      save_highscore_in_file(highscore);
      game_reset();
    }
    if (IsKeyDown(KEY_Q))
    {
      save_highscore_in_file(highscore);
      CloseWindow();
    }
    return;
  }
  if (IsKeyDown(KEY_LEFT))
  {
    spaceship_position.x = spaceship_position.x - 5;
  }
  else if (IsKeyDown(KEY_RIGHT))
  {
    spaceship_position.x = spaceship_position.x + 5;
  }
  if (IsKeyDown(KEY_SPACE))
  {
    spaceship_fire_laser();
  }

  if (IsKeyDown(KEY_Q))
  {
    save_highscore_in_file(highscore);
    CloseWindow();
  }
  if (IsKeyPressed(KEY_P))
  {
    game_is_paused = !game_is_paused;
  }
  if (IsKeyPressed(KEY_N))
  {
    game_level_completed();
  }
}
