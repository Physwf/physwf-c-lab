#include "hash.h"
#include "cocos2d.h"

class Properties
{
public:
	Properties();
	Properties(size_t size);
	~Properties();

	int readFile(const char* filename);
	cocos2d::CCPoint* getPoint(const char* key);
	cocos2d::CCRect* getRect(const char* key);

private:
	Hash* mHashTable;
	unsigned long mTableSize;
	char** mRawData;
	void** mDataCache;
	char* mDataBlock;

	int splitKeyValue(const char* pair, char* key, char* value);
};