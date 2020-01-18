#include "Grid.h"
#include <iostream>

Grid::Grid(int windowWidth, int windowHeight, int width, int height): windowW(windowWidth), windowH(windowHeight), w(width), h(height), open(width*height)

{
	cellWidth = (windowWidth) / width;
	cellHeight = (windowHeight) / height;

	finishPos = Vec2i(width - 1, height - 1);
	

	for (int i = 0; i < width * height; i++)

	{
		cells.push_back(Cell(i));
		//updateCost(cells.back() , Vec2i(w / 2, h / 2));
	}

	//setRectangleObstacle(Vec2i(10, 10), Vec2i(30, 20));
	//setRectangleObstacle(Vec2i(10, 60), Vec2i(95, 70));
	//setRectangleObstacle(Vec2i(30, 40), Vec2i(99, 55));
	updateCost(cells[0], nullptr, finishPos);
	cells[0].open = true;
	//std::cout << open.size() << std::endl;
	open.add(&cells[0]);
	//std::cout << open.size() << std::endl;
	//open.push_back(&cells[0]);
}

void Grid::setObstacle(Vec2i pos)

{
	Vec2i position = pixelToGrid(pos.x, pos.y);
	int i = index(position.x, position.y);
	cells[i].isObstacle = true;
}

void Grid::update(float rate)

{
	if (clock.getElapsedTime().asSeconds() > rate && !isDone)

	{
		clock.restart();
		int lowestFCost = INT_MAX;
		/*Cell* current = &cells[0];
		std::list<Cell*>::iterator currentIT;
		for (std::list<Cell*>::iterator it = open.begin(); it != open.end(); ++it)

		{
			if ((*it)->fCost <= lowestFCost)

			{
				if ((*it)->fCost == lowestFCost)

				{
					if ((*it)->hCost < (*currentIT)->hCost) current = *it, currentIT = it, lowestFCost = (*it)->fCost;
				}

				else

				{
					lowestFCost = (*it)->fCost, current = *it, currentIT = it;
				}
			}
		}*/

		//std::cout << open.size() << std::endl;
		Cell* current = open.removeFirst();
		
		if (current == nullptr) return;
		//std::cout << open.size() << std::endl;
		Vec2i currentPos = positionFromIndex(current->index);
		//std::cout << currentPos << std::endl;
		
		//std::cout << current->gCost << std::endl;
		current->open = false;
		current->closed = true;
		if (currentPos == finishPos) isDone = true, current->setPath(true), std::cout << "Done" << std::endl;
		//open.erase(currentIT);

		for (int i = 0; i < 8; i++)

		{
			Vec2i relative = adjacents[i];
			Vec2i adjacentPos = currentPos + relative;
			if (inBounds(adjacentPos.x, adjacentPos.y))

			{
				int j = index(adjacentPos.x, adjacentPos.y);
				if (!cells[j].isObstacle)

				{
					//std::cout << relative << " ";
					int better = updateCost(cells[j], current, finishPos);
					//if ((std::find(open.begin(), open.end(), &cells[j]) == open.end()) && &cells[j] && better) open.push_back(&cells[j]), cells[j].open = true, cells[j].closed = false;
					if (!open.contains(&cells[j]))

					{
						if (better && &cells[j] != current) cells[j].open = true, cells[j].closed = false, open.add(&cells[j]);
					}

					else open.updateItem(&cells[j]);
				}
			}
		}
		//std::cout << open << std::endl;
		//open.print();
	}

	if (isDone)

	{
		std::cout << (float)performance.getElapsedTime().asMicroseconds() / 1000.0 << " ms" << std::endl;
	}
}

void Grid::draw(sf::RenderWindow& window)

{
	int maxF = -1;
	for (int i = 0; i < cells.size(); i++)

	{
		if (cells[i].gCost > maxF && cells[i].gCost != INT_MAX) maxF = cells[i].gCost;
	}

	sf::RectangleShape rectangle(sf::Vector2f(cellWidth, cellHeight));


	for (int i = 0; i < cells.size(); i++)

	{
		Vec2i pos = positionFromIndex(i);
		rectangle.setPosition(pos.x * cellWidth, pos.y * cellHeight);

		if (maxF == 0) maxF = 1;
		int color = 255 - ((cells[i].gCost * 255) / (maxF)) + 10;
		if (color > 255) color = 255;

		sf::Color sfColor = sf::Color::White;
		rectangle.setFillColor(sfColor);
		if (cells[i].isObstacle) rectangle.setFillColor(sf::Color::Black);
		if (cells[i].open) rectangle.setFillColor(sf::Color(color,0,0));
		if (cells[i].closed) rectangle.setFillColor(sf::Color(0,color,0));
		if (cells[i].isPath) rectangle.setFillColor(sf::Color(0, 0, color));
		
		
		window.draw(rectangle);
		
	}
}

void Grid::setRectangleObstacle(Vec2i tL, Vec2i bR)

{
	for (int i = 0; i < cells.size(); i++)

	{
		Vec2i p = positionFromIndex(i);
		if (p.x >= tL.x && p.x <= bR.x && p.y >= tL.y && p.y <= bR.y) cells[i].isObstacle = true;
	}
}

void Grid::setRectangleObstacleFromMouse(Vec2i topLeft, Vec2i bottomRight)

{
	Vec2i tl = pixelToGrid(topLeft.x, topLeft.y);
	Vec2i br = pixelToGrid(bottomRight.x, bottomRight.y);
	setRectangleObstacle(tl, br);
}

int Grid::updateCost(Cell& cell, Cell* newParent, Vec2i finish)

{
	
	Vec2i posCurrent = positionFromIndex(cell.index);
	int gCostNew, hCostNew, fCostNew;

	hCostNew = std::floor(10.0 * distance(Vec2f(finish.x, finish.y), Vec2f(posCurrent.x, posCurrent.y)));

	if (newParent != nullptr)

	{
		Vec2i posParent = positionFromIndex(newParent->index);
		int dist = distanceSquared(posCurrent, posParent);
		if (dist == 2) dist = 14;
		else if (dist == 1) dist = 10;
		gCostNew = newParent->gCost + dist;
	}

	else

	{
		cell.fCost = hCostNew;
		cell.gCost = 0;
		cell.hCost = hCostNew;
		return 1;
	}
	
	fCostNew = gCostNew + hCostNew;

	if (gCostNew < cell.gCost)

	{
		//std::cout << fCostNew << std::endl;
		cell.fCost = fCostNew;
		cell.gCost = gCostNew;
		cell.hCost = hCostNew;
		cell.parent = newParent;
		return 1;
	}

	return 0;
}