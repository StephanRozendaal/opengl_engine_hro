#include "window.h"

Window::Window(int width, int height) :
		window(sf::VideoMode(width, height), "OpenGL window"), renderer(width,
				height), camera(45.0f, glm::ivec2(width, height),
				glm::vec2(0.1f, 1000.0f)) {
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	Frame frame, frame2;
	frame.translate_local(glm::vec3(0.0f, 0.0f, 0.0f));
	entities.push_back(frame);
	//frame2.translate_local(glm::vec3(0.0f, 10.0f, 10.0f));
	//entities.push_back(frame2);
	central_mouse_position.x = (width / 2);
	central_mouse_position.y = (height / 2);
}

Window::~Window() {
	window.close();
}

void Window::run() {
	bool redraw = true;
	window.setActive();
	sf::Clock clock;
	while (window.isOpen()) {
		while (clock.getElapsedTime() <= sf::Time(sf::seconds(1.0f / 30))) {
		}
		sf::Event event;
		sf::Vector2i current_mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2i mouse_deltas = central_mouse_position  - current_mouse_position;
		mouse_deltas = sf::Vector2i(((-mouse_deltas.x) * 3.5f),
				(mouse_deltas.y) * 3.5f);
		camera.RotateByMouse(glm::vec2(mouse_deltas.x, mouse_deltas.y));
		camera.Update();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			camera.Move(glm::vec3(-1.0f, 0.0f, 0.0f));
			camera.Update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			camera.Move(glm::vec3(1.0f, 0.0f, 1.0f));
			camera.Update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			camera.Move(glm::vec3(0.0f, 0.0f, -1.0f));
			camera.Update();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			camera.Move(glm::vec3(0.0f, 0.0f, 1.0f));
			camera.Update();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			GlobalShaderManager::instance()->set_next_value();
		}
		std::vector<Frame>::iterator it;
		for (it = entities.begin(); it != entities.end(); it++)
			renderer.draw(camera, (*it));
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // window closed.
				window.close();
		}
		clock.restart();
		sf::Mouse::setPosition(central_mouse_position, window);
	}
}
