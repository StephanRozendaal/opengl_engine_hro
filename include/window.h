#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Window.hpp>
#include "renderer.h"

class Window {
 public:
  Window(int, int);
  ~Window();
  void run();
 private:
  sf::Window window;
  Renderer renderer;
};

#endif //WINDOW_H
