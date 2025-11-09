// Normal Libraries
#include <iostream>
#include <math.h>
#include <cstdlib>
// SFML Libraries
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
// Using namespaces
using namespace std;
using namespace sf;


int main() 
{
  RenderWindow window(VideoMode({800, 600}), "SFML window");
  window.setFramerateLimit(60);


  const Texture texture("sprites/player.png");
  Sprite sprite(texture);
  Vector2f position = {400, 300};

  while (window.isOpen()) 
  {
    while (const optional event = window.pollEvent()) 
    {
      if (event->is<Event::Closed>())
        window.close();
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::Left))
      position.x -= 5;
    if (Keyboard::isKeyPressed(Keyboard::Key::Right))
      position.x += 5;
    sprite.setPosition(position);
    window.clear();
    window.draw(sprite);
    window.display();
  }
}
