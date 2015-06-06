#ifndef _GAME_CONNECTION_POOL
#define _GAME_CONNECTION_POOL

#include "Message.h"
#include <map>

typedef struct
{
	GameConnection* connection;
	unsigned char status;
	int refCount;
} PooledConnection;

#define CONN_STATUS_IDLE	0
#define CONN_STATUS_NORMAL	1
#define CONN_STATUS_BUZY	2

typedef std::map<GameConnection*, PooledConnection*> map_con;
class GameConnectionPool : Object
{
private:
	GameConnectionPool();
	~GameConnectionPool();
public:
	void initialize(EventLoop* loop);
	GameConnection* getConnection();
	void recycle(GameConnection*);

	static GameConnectionPool* getInstance();
private:
	void onConnected(GameConnection* conn);
	void onClose(GameConnection* conn);
	void setEventListener(GameConnection* conn);
private:
	static GameConnectionPool* pPool;
	EventLoop* pLoop;
	map_con mConnections;
};
#endif