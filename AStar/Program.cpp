#include "Program.h"

Program::Program(int width, int height) : w(width), h(height), grid(width, height, 100, 100), window(sf::VideoMode(width, height), "A*")

{

}

int Program::mainLoop()

{
	if (!window.isOpen())

	{
		return EXIT_FAILURE;
	}

	sf::Event events;

	//std::thread worker(&Program::update, this);

	while (window.isOpen())

	{
		while (window.pollEvent(events))

		{
			if (events.type == sf::Event::EventType::Closed)

			{
				window.close();
			}

			eventHandler(events);
		}
		//Update
		mtx.lock();
		int done = grid.isDone;
		mtx.unlock();
		if (worker != nullptr && worker->joinable() && done) worker->join();
		//update();
		//
		//Draw
		draw();
		//
		window.display();
	}
	if (worker != nullptr && worker->joinable()) worker->join();
	return EXIT_SUCCESS;
}

void Program::threadCallback(const void* p)

{
	Program* instance = (Program*)p;
	instance->update();
}

void Program::update()

{
	while (!grid.isDone)

	{
		mtx.lock();
		grid.update(0.001);
		mtx.unlock();
	}
}

void Program::draw()

{
	if (clock.getElapsedTime().asSeconds() > 0.01)

	{
		window.clear();
		clock.restart();
		mtx.lock();
		Grid buffer = grid;
		mtx.unlock();
		buffer.draw(window);
	}
	sf::RectangleShape rect(sf::Vector2f(20, 20));
	rect.setPosition(topLeft.x - 10, topLeft.y - 10);
	rect.setFillColor(sf::Color::Green);
	if (count == 1) window.draw(rect);
}

void Program::eventHandler(sf::Event events)

{

	if (events.type == sf::Event::EventType::KeyPressed)

	{
		if (events.key.code == sf::Keyboard::Enter)

		{
			worker = std::unique_ptr<std::thread>(new std::thread(&Program::update, this));
			grid.performance.restart();
		}
	}

	else if (events.type == sf::Event::EventType::MouseButtonPressed)

	{
		if (events.mouseButton.button == sf::Mouse::Right)

		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			if (count == 0) topLeft = Vec2i(pos.x, pos.y);
			else if (count == 1) bottomRight = Vec2i(pos.x, pos.y), grid.setRectangleObstacleFromMouse(topLeft, bottomRight);
			count = (count + 1) % 2;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))

	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		grid.setObstacle(Vec2i(pos.x+1, pos.y));
		grid.setObstacle(Vec2i(pos.x-1, pos.y));
		grid.setObstacle(Vec2i(pos.x, pos.y+1));
		grid.setObstacle(Vec2i(pos.x, pos.y-1));
		grid.setObstacle(Vec2i(pos.x, pos.y));
	}
}