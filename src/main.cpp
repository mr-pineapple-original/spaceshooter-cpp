// Normal
#include <iostream>
#include <math.h>
#include <cstdlib>
// SFML 
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
  RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
  window.setFramerateLimit(60);
  const Texture texture("../sprites/player.png");
  Sprite sprite(texture);
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear();
    window.draw(sprite);
    window.display();
  }

}
