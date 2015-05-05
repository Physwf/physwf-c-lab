#ifndef _BUFFER_H
#define _BUFFER_H

class Buffer
{
public :
	Buffer(size_t size);
	~Buffer();
public:
	size_t append(const char* data, size_t size);
	//size_t append(const char* data) { return append(data, sizeof()) }
	size_t append(Buffer &buf) { return append(buf.data(), buf.avaliable()); }

	char* data();
	void clear();
	size_t position(size_t pos);
	size_t avaliable();
private:
	char* pBuffer;
	size_t nAvaliable;
	size_t nPosition;
};

#endif