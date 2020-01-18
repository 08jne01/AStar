#pragma once
#include <mutex>
#include <thread>
#include "Grid.h"

class Program

{
public:
	Program(int height, int width);
	int mainLoop();
	void draw();
	void update();
	void eventHandler(sf::Event events);
	static void threadCallback(const void* p);
private:
	int w, h;
	bool shouldUpdate = true;
	sf::RenderWindow window;
	Grid grid;
	sf::Clock clock;
	std::mutex mtx;
	std::unique_ptr<std::thread> worker;
	int count = 0;

	Vec2i topLeft, bottomRight;
};