#pragma once
#include <vector>
#include <string>
template <class T> class Heap

{
public:
	Heap(int size): heap(size)

	{

	}

	unsigned int parent(const int& index) const

	{
		return (index - 1) / 2;
	}

	unsigned int left(const int& index) const

	{
		return 2 * index + 1;
	}

	unsigned int right(const int& index) const

	{
		return 2 * index + 2;
	}

	bool contains(const T* item) const

	{
		return (heap[item->heapIndex] == item);
	}

	void updateItem(T* item)

	{
		sortUp(item);
	}

	void updateTop()

	{
		sortDown(heap[0]);
	}

	T* removeFirst()

	{
		if (heapIndex > 0)

		{
			T* firstItem = heap[0];
			heapIndex--;
			heap[0] = heap[heapIndex];
			heap[0]->heapIndex = 0;
			sortDown(heap[0]);
			return firstItem;
		}

		return nullptr;
	}

	void add(T* item)

	{
		item->heapIndex = heapIndex;
		heap[heapIndex] = item;
		sortUp(heap[heapIndex]);
		heapIndex++;
	}

	void sortDown(T* item)

	{
		while (true)

		{
			
			unsigned int childLeft = left(item->heapIndex);
			unsigned int childRight = right(item->heapIndex);
			unsigned int swapIndex = 0;
			if (childLeft < heapIndex)

			{
				swapIndex = childLeft;
				if (childRight < heapIndex)

				{
					if (heap[childLeft]->compareTo(*heap[childRight]) < 0) swapIndex = childRight;
				}

				if (item->compareTo(*heap[swapIndex]) < 0)

				{
					swap(item, heap[swapIndex]);
				}

				else return;
			}

			else return;
		}
	}

	void sortUp(T* item)

	{
		
		while (true)

		{
			short parentIndex = parent(item->heapIndex);
			T* parentItem = heap[parentIndex];
			if (item->compareTo(*parentItem) > 0) swap(item, parentItem);
			else break;
		}
	}

	void swap(T* item1, T* item2)

	{
		heap[item1->heapIndex] = item2;
		heap[item2->heapIndex] = item1;
		int item1Index = item1->heapIndex;
		item1->heapIndex = item2->heapIndex;
		item2->heapIndex = item1Index;
	}

	unsigned int size() const

	{
		return heapIndex;
	}

	

	void print()

	{

		std::cout << std::endl;

		for (int i = 0; i < heapIndex; i++)

		{
			std::cout << i << "  ";
		}

		std::cout << std::endl;

		for (int i = 0; i < heapIndex; i++)

		{
			std::cout << parent(i) << "  ";
		}

		std::cout << std::endl;

		for (int i = 0; i < heapIndex; i++)

		{
			std::cout << heap[i]->fCost << "  ";
		}

		std::cout << std::endl;
	}

	T* operator[] (const int& index) const

	{
		return heap[index];
	}

	void formatedHeap(std::vector<std::vector<int>>& levels, int level)

	{
		int numLevels = log2(heapIndex + 1);
		std::vector<int> thisLevel;
		for (int i = 0; i < pow(2, level); i++)

		{

		}
	}

private:
	std::vector<T*> heap;
	unsigned int heapIndex = 0;
};

template <class T> std::ostream& operator<<(std::ostream& os, const Heap<T>& heap)

{
	int level = 0;
	int total = 0;
	int width = pow(2, log2(heap.size() + 1) - 1);
	//std::vector<std::vector<int>> formated;
	//std::vector<int> formatedLevel;
	for (int i = 0; i < heap.size(); i++)

	{

		//std::cout << std::endl << "total " << total << " " << pow(2, level) << std::endl;
		//formatedLevel.push_back(heap[i]->fCost);

		for (int j = 0; j < width / (level + 2) && total == 0; j++)

		{
			os << "   ";
		}

		os << (heap[i])->fCost << "   ";
		total++;
		if (total >= pow(2, level)) os << std::endl, total = 0, level++;
		//if (total >= pow(2, level)) level++, total = 0, formated.push_back(formatedLevel), formatedLevel.clear();
	}

	/*int width = formated.back().size();

	for (int j = 0; j < formated.size(); j++)

	{
		int count = 0;
		for (int i = 1; i < 2*width; i++)

		{
			if (i % formated[j].size() == 0) os << formated[j][count] << " ", count++;
			else os << "------";
		}

		os << std::endl;
	}*/
	

	return os;
}

class Item

{
public:
	Item()

	{

	}
	unsigned int heapIndex = -1;
};

typedef Heap<int> HeapInt;
typedef Heap<double> HeapDouble;
typedef Heap<float> HeapFloat;