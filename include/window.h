#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Window.hpp>
#include "renderer.h"
#include "camera.h"
#include "frame.h"
#include "shader.h"
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
  sf::Vector2i central_mouse_position; // midden van het Window.
};

#endif //WINDOW_H
