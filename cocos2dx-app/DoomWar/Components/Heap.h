#ifndef _HEAP_H
#define _HEAP_H

class IPriority
{
public:
	int virtual value() const = 0;
};

class MaxHeap
{
public:
	MaxHeap(unsigned int capacity);
	void Enqueue(IPriority* item);
	IPriority* Dequeue();
	unsigned int size() const;
	bool hasItem(IPriority* item);
	IPriority* getMax()const;
private:
	unsigned int mSize;
	IPriority** mHeap;
};

class MinHeap
{
public:
	MinHeap(unsigned int capacity);
	void Enqueue(IPriority* item);
	IPriority* Dequeue();
	unsigned int size() const;
	bool hasItem(IPriority* item);
	IPriority* getMin()const;
private:
	unsigned int mSize;
	IPriority** mHeap;
};

#endif