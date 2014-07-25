#include "Properties.h"
#include "log/Log.h"

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
	char c;
	while ((c = fgetc(pFile)) != EOF) {
		len++;
		Log::info("%c", c);
		if (c == '\n')
		{
			fseek(pFile, -len, SEEK_CUR);
			fgets(data, len, pFile);
			data[len - 1] = '\0';
			len=0;
			char key[512], value[512];
			int valueLen;
			if (valueLen = splitKeyValue(data, key, value))
			{
				Hash* entry = get_hash_entry(mHashTable, key, mTableSize);
				memcpy(block, value, valueLen*sizeof(char));
				mRawData[entry->index] = block;
				block += valueLen;
				numProperites++;
			}
		}
	};
	return 0;
};

cocos2d::CCPoint* Properties::getPoint(const char* key)
{
	Hash* entry = get_hash_entry(mHashTable, key, mTableSize);
	if (entry != NULL && mDataCache[entry->index])
	{
		return (cocos2d::CCPoint*)mDataCache[entry->index];
	}
	char* data = mRawData[entry->index];
	if (data)
	{

	}
	return NULL;

};

int Properties::splitKeyValue(const char* pair, char* key, char* value)
{
	key = strtok((char*)pair, "=");
	if (key == NULL) return 0;
	value = strtok(NULL, "=");
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
	}
	object->origin.x = coords[0];
	object->origin.y = coords[1];
	object->size.width = coords[2];
	object->size.height = coords[3];
	return 0;
};