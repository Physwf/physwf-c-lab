#include "Buffer.h"

Buffer::Buffer()
{
	nPosition = 0;
	nSize = 0;
	resize(64);
}

Buffer::Buffer(size_t hint)
{
	nPosition = 0;
	nSize = 0;
	resize(hint);
}

Buffer::Buffer(const char* buf, size_t hint):Buffer(hint)
{
	append(buf, hint);
}

Buffer::~Buffer()
{
	free(pBuffer);
}

size_t Buffer::append(const char* buf, size_t size)
{
	size_t tailFree = nCapacity - nPosition;
	if (tailFree < size)
		resize(nSize + size);
	nSize += size;
	memcpy(pBuffer + nPosition, buf, size);
	return nSize;
}

void Buffer::resize(size_t newsize)
{
	int newCapacity = 64;
	while (newCapacity < newsize)
		newCapacity *= 2;
	if (newCapacity > nCapacity)
	{
		pBuffer = (char*)realloc(pBuffer, newCapacity);
		nCapacity = newCapacity;
	}
}