#pragma once
#include <assert.h>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Maths.h"
#include "Cell.h"

class Grid

{
public:
	Grid(int windowWidth, int windowHeight, int width, int height);
	void draw(sf::RenderWindow& window);
	void update(float rate);
	int updateCost(Cell& cell, Cell* newParent, Vec2i finish);
	void setObstacle(Vec2i pos);
	void setRectangleObstacle(Vec2i topLeft, Vec2i bottomRight);
	void setRectangleObstacleFromMouse(Vec2i topLeft, Vec2i bottomRight);

	int index(const int& x, const int& y) const

	{
		return x + y * w;
	}

	Vec2i positionFromIndex(const int& index) const

	{
		return Vec2i(index % w, index / w);
	}

	bool inBounds(const int& x, const int& y) const

	{
		return (x >= 0 && x < w && y >= 0 && y < h);
	}

	Vec2i pixelToGrid(const int& x, const int& y)

	{
		return Vec2i(x / cellWidth, y / cellHeight);
	}
	
	std::vector<Cell> cells;
	//std::list<Cell*> open;
	Heap<Cell> open;
	bool isDone = false;
	sf::Clock performance;
private:
	int w, h, windowW, windowH, cellWidth, cellHeight;
	sf::Clock clock;
	
	Vec2i finishPos = Vec2i(99, 99);
	Vec2i adjacents[8] = { {-1, -1}, {0, -1}, {1, -1}, {1,0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0} };
};