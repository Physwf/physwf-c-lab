#include "Heap.h"
#include <stdlib.h>
#include <string.h>

MaxHeap::MaxHeap(unsigned int capacity)
{
	mHeap = (IPriority**) malloc(capacity*sizeof(IPriority*));
	mSize = 0;
}

void MaxHeap::Enqueue(IPriority* item)
{
	mHeap[mSize] = item;
	int lastIndex = mSize;//最后一个元素的索引
	int parentIndex = (lastIndex - 1) * .5;//最后一个元素的父亲的索引
	mSize++;

	if (lastIndex == 0) return;

	while (mHeap[parentIndex]->value() < item->value())
	{
		mHeap[lastIndex] = mHeap[parentIndex];
		mHeap[parentIndex] = item;
		lastIndex = parentIndex;
		parentIndex = (lastIndex - 1)*.5;
		if (parentIndex<=0) break;
	}
}

IPriority* MaxHeap::Dequeue()
{
	if (mSize == 0) return NULL;

	IPriority* max = mHeap[0];
	mSize--;
	mHeap[0] = mHeap[mSize];

	int parentIndex = 0;
	int childIndex = 2 * parentIndex + 1;
	IPriority* temp = mHeap[parentIndex];

	while (childIndex<mSize)
	{
		if (childIndex + 1<mSize && mHeap[childIndex]<mHeap[childIndex + 1])
			childIndex++;
		if (mHeap[childIndex]->value() <= temp->value())
			break;
		mHeap[parentIndex] = mHeap[childIndex];
		parentIndex = childIndex;
		childIndex = 2 * parentIndex + 1;
	}
	mHeap[parentIndex] = temp;
	return max;
}

unsigned int MaxHeap::size() const
{
	return mSize;
}

bool MaxHeap::hasItem(IPriority* item)
{
	for (unsigned int i = 0; i < mSize; i++)
	{
		if (mHeap[i] == item) return true;
	}
	return false;
}

IPriority* MaxHeap::getMax() const
{
	return mHeap[0];
}

/*MinHeap*/

MinHeap::MinHeap(unsigned int capacity)
{
	mHeap = (IPriority**)malloc(capacity*sizeof(IPriority*));
	mSize = 0;
}

void MinHeap::Enqueue(IPriority* item)
{
	mHeap[mSize] = item;
	unsigned int lastIndex = mSize;//最后一个元素的索引
	int parentIndex = (lastIndex - 1) * .5;
	mSize++;

	if (lastIndex == 0) return;//第一个元素

	while (mHeap[parentIndex]->value() > item->value())
	{
		mHeap[lastIndex] = mHeap[parentIndex];
		mHeap[parentIndex] = item;
		lastIndex = parentIndex;
		parentIndex = (lastIndex - 1) * .5;
		if (parentIndex < 0) break;//说明已经到头
	}
}

IPriority* MinHeap::Dequeue()
{
	if (!mSize) return NULL;
	IPriority* $min = mHeap[0];
	mSize--;
	mHeap[0] = mHeap[mSize];//将堆尾移到堆顶

	int parentIndex = 0;
	int childIndex;
	IPriority* temp;
	temp = mHeap[0];
	childIndex = 2 * parentIndex + 1;
	while (childIndex < mSize)
	{
		if (childIndex + 1 < mSize && mHeap[childIndex + 1]->value() < mHeap[childIndex]->value())
			childIndex++;
		if (mHeap[childIndex]->value() >= temp->value())
			break;
		mHeap[parentIndex] = mHeap[childIndex];
		parentIndex = childIndex;
		childIndex = 2 * parentIndex + 1;
	}
	mHeap[parentIndex] = temp;
	return $min;
}

unsigned int MinHeap::size() const
{
	return mSize;
}

bool MinHeap::hasItem(IPriority* item)
{
	for (unsigned int i = 0; i < mSize; i++)
	{
		if (mHeap[i] == item) return true;
	}
	return false;
}

IPriority* MinHeap::getMin() const
{
	if (!mSize) return NULL;
	return mHeap[0];
}
