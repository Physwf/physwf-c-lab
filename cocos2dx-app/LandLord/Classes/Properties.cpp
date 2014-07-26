#include "Properties.h"
#include "log/Log.h"

Properties::Properties()
{
	mTableSize = 0x100;
	mHashTable = (Hash*)malloc(mTableSize * sizeof(Hash));
	mBlockTable = (Block*)malloc(mTableSize * sizeof(Block));
	mDataBlock = (char*)malloc(1024 * 100 * sizeof(char));
	memset(mHashTable, 0, mTableSize*sizeof(Hash));
	memset(mBlockTable, 0, mTableSize*sizeof(Block));
	memset(mDataBlock, 0, 1024 * 100 *sizeof(char));
	for (unsigned int i = 0; i < mTableSize; i++)
		mHashTable[i].blockIndex = HASH_ENTRY_FREE;
	init_hash_buffer();
};

Properties::Properties(size_t size)
{
	mTableSize = (unsigned long)size;
	mHashTable = (Hash*)malloc(mTableSize * sizeof(Hash));
	mBlockTable = (Block*)malloc(mTableSize * sizeof(Block));
	mDataBlock = (char*)malloc(1024 * 100 * sizeof(char));
	memset(mHashTable, 0, mTableSize*sizeof(Hash));
	memset(mBlockTable, 0, mTableSize*sizeof(Block));
	memset(mDataBlock, 0, 1024 * 100 * sizeof(char));
	for (unsigned int i = 0; i < mTableSize; i++)
		mHashTable[i].blockIndex = HASH_ENTRY_FREE;
	init_hash_buffer();
};

Properties::~Properties()
{
	free(mHashTable);
	free(mBlockTable);
	free(mDataBlock);
};

int Properties::readFile(const char* filename)
{
	FILE* pFile = fopen(filename, "rb");
	char data[1024];
	char* db = mDataBlock;
	int numProperites = 0;
	int len = 0;
	
	Block * block = NULL;

	while (fgets(data,1024,pFile)!= NULL) {
		if (data[0] == '#') continue;
		if (data[0] == '\n') continue;

		char key[512], value[512];
		int valueLen;
		int error = ERROR_SUCCESS;
		if (valueLen = splitKeyValue(data, key, value))
		{
			Hash* entry = get_hash_entry(mHashTable, key, mTableSize);
			if (entry != NULL)
			{
				//to do
				error = ERROR_ALREADY_EXISTS;
			}

			if (error == ERROR_SUCCESS && entry == NULL)
			{
				entry = find_free_hash_entry(mHashTable, mBlockTable, key, mTableSize);
				if (entry == NULL)
					error = ERROR_HANDLE_DISK_FULL;
			}

			if (error == ERROR_SUCCESS)
			{
				Block * pBlockEnd = mBlockTable + mTableSize;
				unsigned long pos = db - mDataBlock;

				memcpy(db, value, strlen(value));
				db += strlen(value);
				block = mBlockTable + entry->blockIndex;
				block->position = pos;
				block->size = strlen(value);
				block->flags |= FLAG_BLOCK_EXSIT;
			}			
			numProperites++;
			
		}
	};
	return 0;
};

cocos2d::CCPoint* Properties::getPoint(const char* key)
{
	Hash* entry = get_hash_entry(mHashTable, key, mTableSize);
	Block* block = mBlockTable + entry->blockIndex;
	char* value = mDataBlock + block->position;
	Log::log("getPoint:%s", value);
	cocos2d::CCPoint* point = new cocos2d::CCPoint();
	splitPoint(value, point);
	return point;
};

cocos2d::CCRect* Properties::getRect(const char* key)
{
	Hash* entry = get_hash_entry(mHashTable, key, mTableSize);
	Block* block = mBlockTable + entry->blockIndex;
	char value[512] = {0};
	memcpy(value, mDataBlock + block->position, block->size);
	Log::log("getPoint:%s", value);
	cocos2d::CCRect* rect = new cocos2d::CCRect();
	splitRect(value, rect);
	return rect;
}

int Properties::splitKeyValue(const char* pair, char* key, char* value)
{
	strcpy(key, strtok((char*)pair,"="));
	//key = strtok((char*)pair, "=");
	if (key == NULL) return 0;
	strcpy(value, strtok(NULL, "="));
	//value = strtok(NULL, "=");
	return strlen(value);
};

int Properties::splitPoint(const char* point, cocos2d::CCPoint* object)
{
	char* coord = strtok((char*)point, ",");
	int coords[2];
	int i = 0;
	while (coord != NULL)
	{
		coords[i++] = atoi(coord);
		if (i > 2)
		{
			// warning
			break;
		}
	}
	object->x = coords[0];
	object->y = coords[1];
	return 0;
};

int Properties::splitRect(const char* rect, cocos2d::CCRect* object)
{
	char* coord = strtok((char*)rect, ",");
	int coords[4];
	int i = 0;
	while (coord != NULL)
	{
		coords[i++] = atoi(coord);
		if (i > 4)
		{
			// warning
			break;
		}
		coord = strtok(NULL, ",");
	}
	object->origin.x = coords[0];
	object->origin.y = coords[1];
	object->size.width = coords[2];
	object->size.height = coords[3];
	return 0;
};