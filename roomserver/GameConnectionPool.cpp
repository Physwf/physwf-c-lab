#include "GameConnectionPool.h"

GameConnectionPool::GameConnectionPool()
{

}

GameConnectionPool::~GameConnectionPool()
{

}

void GameConnectionPool::initialize(EventLoop* loop)
{
	pLoop = loop;
	for (int i = 0; i < 1;i++)
	{
		GameConnection* gConn = new GameConnection(pLoop);
		gConn->setConnectHandler(EV_CB(this,GameConnectionPool::onConnected));
		gConn->setCloseHandler(EV_CB(this, GameConnectionPool::onClose));
	}
}

GameConnection* GameConnectionPool::getConnection()
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

void GameConnectionPool::recycle(GameConnection*)
{

}

void GameConnectionPool::onConnected(GameConnection* conn)
{
	PooledConnection* pCon = new PooledConnection();
	pCon->connection = conn;
	pCon->refCount = 0;
	pCon->status = CONN_STATUS_IDLE;
	mConnections.insert(map_con::value_type(conn, pCon));
}

GameConnectionPool* GameConnectionPool::pPool = NULL;

GameConnectionPool* GameConnectionPool::getInstance()
{
	if (!pPool)
	{
		pPool = new GameConnectionPool();
	}
	return pPool;
}


