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
	int splitKeyValue(const char* pair, char* key, char* value);
	int splitPoint(const char* point, cocos2d::CCPoint* object);
	int splitRect(const char* rect, cocos2d::CCRect* object);
private:
	Hash* mHashTable;
	Block* mBlockTable;
	unsigned long mTableSize;
	char* mDataBlock;
};