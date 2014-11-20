#include "serialization.h"
#include <assert.h>
#include <string.h>

char readByte(Bytes* input)
{
	assert(input->position+sizeof(char) < input->length);
	char* data = input->data + input->position;
	char c = *(data);
	input->position += sizeof(char);
	return c;
}

unsigned char readUnsignedByte(Bytes* input)
{
	assert(input->position+sizeof(char) < input->length);
	char* data = input->data + input->position;
	unsigned char c = (unsigned char )*(data);//any problem
	input->position += sizeof(char);
	return c;
}

short readShort(Bytes* input)
{
	assert(input->position+sizeof(short) < input->length);
	char* data = input->data + input->position;
	short v;
	memcpy(&v, data, sizeof(short));
	input->position += (sizeof(short)/sizeof(char));
	return v;
}

unsigned short readUnsignedShort(Bytes* input)
{
	assert(input->position+sizeof(short) < input->length);
	char* data = input->data + input->position;
	unsigned short v;
	memcpy(&v, data, sizeof(short));
	input->position += (sizeof(short)/sizeof(char));
	return v;
}

int readInt(Bytes* input)
{
	assert(input->position+sizeof(int) < input->length);
	char* data = input->data + input->position;
	int v;
	memcpy(&v, data, sizeof(int));
	input->position += (sizeof(int)/sizeof(char));
	return v;
}

unsigned int readUnsignedInt(Bytes* input)
{
	assert(input->position+sizeof(int) < input->length);
	char* data = input->data + input->position;
	unsigned int v;
	memcpy(&v, data, sizeof(int));
	input->position += (sizeof(int)/sizeof(char));
	return v;
}

Bytes* readBytes(Bytes* input, Bytes* output, int offset, int length)
{
	assert(input->position + length < input->length);
	assert(output->position + length < output->length);
	
	memcpy(output->data, input->data, length);
	input->position += length;
	return output;
}

void writeByte(Bytes* output,char v)
{
	assert(output->position+sizeof(char) < output->length);
	char* data = output->data + output->position;
	memcpy(data, &v, sizeof(char));
	output->position += sizeof(char);
}

void writeShort(Bytes* output, short v)
{
	assert(output->position+sizeof(short) < output->length);
	char* data = output->data + output->position;
	memcpy(data, &v, sizeof(short));
	output->position += sizeof(short);
}

void writeInt(Bytes* output,int v)
{
	assert(output->position+sizeof(int) < output->length);
	char* data = output->data + output->position;
	memcpy(data, &v, sizeof(int));
	output->position += sizeof(int);
}
void writeUnsignedInt(Bytes* output, unsigned int v)
{
	assert(output->position+sizeof(int) < output->length);
	char* data = output->data + output->position;
	memcpy(data, &v, sizeof(int));
	output->position += sizeof(int);
}

void writeBytes(Bytes* output, Bytes* bytes, int offset, int length)
{
	assert(output->position + length < output->length);
	assert(bytes->position + length < bytes->length);
	
	char* out = bytes->data + offset;
	char* in = output->data + output->position;
	
	memcpy(out, in, length);
	
	output->position += length;
}