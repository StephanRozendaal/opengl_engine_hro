#include "window.h"

Window::Window(int width, int height) : window(sf::VideoMode(width, height), "OpenGL window"), renderer(width, height) {
 
}

Window::~Window() {
  window.close();
}

void Window::run() {
  bool redraw = true;
  window.setActive();

  while(window.isOpen()) {
    sf::Event event;
    //doe event dingen
    if(redraw) {
      renderer.draw();
      window.display();
      redraw = false;
    }
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed)
	window.close();
      // if(event.Type == sf::Event::KeyPressed) 
    }
  }
}
