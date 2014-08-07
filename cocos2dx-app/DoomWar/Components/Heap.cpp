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
	int lastIndex  = mSize;//最后一个元素的索引
	int parentIndex = (lastIndex - 1) * .5;//最后一个元素的父亲的索引
	mSize++;

	if (lastIndex == 0) return;

	while (mHeap[parentIndex]->value() < item->value())
	{
		mHeap[lastIndex] = mHeap[parentIndex];
		mHeap[parentIndex] = item;
		lastIndex = parentIndex;
		parentIndex = (lastIndex - 1)*.5;
		if (parentIndex<0) break;
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


