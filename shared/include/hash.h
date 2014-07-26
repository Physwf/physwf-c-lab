#define HASH_ENTRY_DELETED       0xFFFFFFFE // Block index for deleted hash entry
#define HASH_ENTRY_FREE          0xFFFFFFFF // Block index for free hash entry

#define FLAG_BLOCK_EXSIT		0x80000000

typedef struct hash_t
{
	unsigned long keyA;
	unsigned long keyB;
	unsigned long index;
	unsigned long blockIndex;
}
Hash, *PHash;

typedef struct block_t
{
	unsigned long position;
	unsigned long size;
	unsigned long flags;
} Block;

int init_hash_buffer();
unsigned long hash_index(unsigned long table_size,const char* key);
unsigned long hash_keyA(const char* key);
unsigned long hash_keyB(const char* key);
Hash* get_hash_entry(Hash* table,const char* key,unsigned long table_size);
Hash* find_free_hash_entry(Hash* hTable, Block* bTable, const char* key, unsigned long table_size);
