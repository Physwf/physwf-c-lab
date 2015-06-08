#include "GamePool.h"

GamePool::GamePool()
{

}

GamePool::~GamePool()
{

}

void GamePool::initialize(EventLoop* loop)
{
	pLoop = loop;
	for (int i = 0; i < 1;i++)
	{
		GameConnection* gConn = new GameConnection(pLoop);
		gConn->setConnectHandler(EV_CB(this,GamePool::onConnected));
		gConn->setCloseHandler(EV_CB(this, GamePool::onClose));
	}
}

Game* GamePool::getGame()
{
	GameConnection* con = getConnection();
	Game* game = NULL;
	if (con)
	{
		for (map_game::iterator it = mGames.begin(); it != mGames.end(); it++)
		{
			if (it->second->isIdle())
			{
				game = it->second;
				game->start(con);
				return game;
			}
		}

		game = new Game();
		game->start(con);
		mGames.insert(map_game::value_type(game->iid(), game));
		return game;
	}
	return NULL;
}

void GamePool::recycle(Game* game)
{
	game->end();
}

void GamePool::onConnected(GameConnection* conn)
{
	PooledConnection* pCon = new PooledConnection();
	pCon->connection = conn;
	pCon->refCount = 0;
	pCon->status = CONN_STATUS_IDLE;
	mConnections.insert(map_con::value_type(conn, pCon));
}


void GamePool::onGameMessage(char* head, size_t hsize, char* body, size_t bsize)
{
	MSG_HEAD_GAME gHead;
	read_head_game(head, &gHead);
	map_game::iterator it = mGames.find(gHead.iid);
	if (it != mGames.end())
	{
		it->second->handleMessage(&gHead,body);
	}
}

GameConnection* GamePool::getConnection()
{
	for (map_con::iterator it = mConnections.begin(); it != mConnections.end(); it++)
	{
		PooledConnection *poc = it->second;
		if (poc->status < CONN_STATUS_NORMAL)
		{
			poc->refCount++;
			return poc->connection;
		}
	}
	return NULL;
}

GamePool* GamePool::pPool = NULL;

GamePool* GamePool::getInstance()
{
	if (!pPool)
	{
		pPool = new GamePool();
	}
	return pPool;
}


