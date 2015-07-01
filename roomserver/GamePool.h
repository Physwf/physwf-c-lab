#ifndef _GAME_CONNECTION_POOL
#define _GAME_CONNECTION_POOL

#include "Message.h"
#include "Table.h"
#include "Game.h"
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
typedef std::map<iid_t, Game*> map_game;

class GamePool : Object
{
private:
	GamePool();
	~GamePool();
public:
	void initialize(EventLoop* loop);
	Game* getGame();
	void recycle(Game* game);

	static GamePool* getInstance();
private:
	void onConnected(GameConnection* conn);
	void onGameMessage(GameConnection* conn, MSG_HEAD_GAME* head, char* body);
	void onClose(GameConnection* conn);
	GameConnection* getConnection();
private:
	static GamePool* pPool;
	EventLoop* pLoop;
	MessageHandler cbTableHandler;
	map_con mConnections;
	map_game mGames;
};
#endif