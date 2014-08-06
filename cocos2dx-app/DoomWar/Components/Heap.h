#ifndef _HEAP_H
#define _HEAP_H

class IPriority
{
	int virtual getValue()const = 0;
};

class MaxHeap
{
public:
	MaxHeap(unsigned int capacity);
	void Enqueue(IPriority* item);
	IPriority* Dequeue();
	unsigned int size();
	bool hasItem(IPriority* item);
	IPriority* getMax()const;
private:
	unsigned int mSize;
	IPriority* mHeap;
};

#endif