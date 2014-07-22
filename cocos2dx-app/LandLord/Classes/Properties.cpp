#include "Properties.h"

Properties::Properties()
{
	mTableSize = 0x100;
	mHashTable = (Hash*)malloc(mTableSize * sizeof(Hash));
	mRawData = (char**)malloc(mTableSize * sizeof(char*));
	mDataCache = (void**)malloc(mTableSize * sizeof(void*));
	mDataBlock = (char*) malloc(1024*100*sizeof(char));
	memset(mRawData, 0, mTableSize * sizeof(char*));
	memset(mDataCache, 0, mTableSize * sizeof(void*));
	init_hash_buffer();
};

Properties::Properties(size_t size)
{
	mTableSize = (unsigned long)size;
	mHashTable = (Hash*)malloc(mTableSize * sizeof(Hash));
	mRawData = (char**)malloc(mTableSize * sizeof(char*));
	mDataCache = (void**)malloc(mTableSize * sizeof(void*));
	mDataBlock = (char*)malloc(1024 * 100 * sizeof(char));
	memset(mRawData, 0, mTableSize * sizeof(char*));
	memset(mDataCache, 0, mTableSize * sizeof(void*));
	init_hash_buffer();
};

Properties::~Properties()
{
	free(mHashTable);
	free(mDataCache);
	free(mRawData);
	free(mDataBlock);
};

int Properties::readFile(const char* filename)
{
	FILE* pFile = fopen(filename, "rb");
	char data[1024];
	char* block = mDataBlock;
	int numProperites = 0;
	int len = 0;
	do{
		char c = fgetc(pFile);
		len++;
		if (c == '\n')
		{
			fseek(pFile, len*-1, SEEK_CUR);
			fgets(data, len, pFile);
			data[len - 1] = '\0';
			len=0;
			char key[512], value[512];
			int valueLen;
			if (valueLen = splitKeyValue(data, key, value))
			{
				Hash* entry = get_hash_entry(mHashTable, key);
				memcpy(block, value, valueLen*sizeof(char));
				block += valueLen;

				numProperites++;
			}
		}
	} while (fgetc(pFile) != EOF);
	return 0;
};

cocos2d::CCPoint* Properties::getPoint(const char* key)
{
	Hash* entry = get_hash_entry(mHashTable, key);
	if (entry != NULL && mDataCache[entry->index])
	{
		return (cocos2d::CCPoint*)mDataCache[entry->index];
	}
	return NULL;

};

int splitKeyValue(const char* pair, char* key, char* value)
{
	key = strtok((char*)pair, "=");
	if (key == NULL) return 0;
	value = strtok(NULL, "=");
	return strlen(value);
};