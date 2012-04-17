#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Window.hpp>
#include "renderer.h"
#include "camera.h"
#include "frame.h"
class Window {
 public:
  Window(int, int);
  ~Window();
  void run();
 private:
  sf::Window window;
  Renderer renderer;
  Camera camera;
  std::vector<Frame> entities;
};

#endif //WINDOW_H
