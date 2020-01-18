#pragma once
#include "Heap.h"
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

class Cell : public Item

{
public:

	Cell()

	{

	}

	Cell(const int index_): index(index_)

	{

	}

	Cell(const int index_, bool obstacle) : index(index_), isObstacle(obstacle)

	{

	}

	bool operator== (const Cell& cell) const

	{
		return (index == cell.index && parent == cell.parent);
	}

	int compareTo(Cell& cell)

	{
		int compare = 0;
		if (fCost < cell.fCost) compare = 1;
		else if (fCost > cell.fCost) compare = -1;
		
		if (compare == 0)

		{
			if (hCost < cell.hCost) compare = 1;
			else if (hCost > cell.hCost) compare = -1;
		}
		return compare;
	}

	void setPath(bool path)

	{
		isPath = path;
		if (parent != nullptr)

		{
			parent->setPath(path);
		}
	}

	int index;
	bool isObstacle = false;
	bool open = false;
	bool closed = false;
	bool isPath = false;
	int gCost = INT_MAX;
	int hCost;
	int fCost = INT_MAX;
	Cell* parent = nullptr;
};