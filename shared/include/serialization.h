typedef struct bytes_t
{
	char* data;
	unsigned int position;
	unsigned length;
} Bytes, *PBytes;

char readByte(Bytes* input);
unsigned char readUnsignedByte(Bytes* input);

short readShort(Bytes* input);
unsigned short readUnsignedShort(Bytes* input);

int readInt(Bytes* input);
unsigned int readUnsignedInt(Bytes* input);

Bytes* readBytes(Bytes* input, Bytes* output, int offset, int lenght);

void writeByte(Bytes* output,char v);

void writeShort(Bytes* output, short v);

void writeInt(Bytes* output,int value);
void writeUnsignedInt(Bytes* output, unsigned int v);

void writeBytes(Bytes* output, Bytes* bytes,int offset, int length);