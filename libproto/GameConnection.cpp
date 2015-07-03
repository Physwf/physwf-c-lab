#include "GameConnection.h"
#include "Log.h"

GameConnection::GameConnection(EventLoop* loop, int fd /*= INVALID_SOCKET*/)
{
	pConnection = new Connection(loop, fd);
	init();
}

GameConnection::GameConnection(Connection* con) :pConnection(con)
{
	init();
}

void GameConnection::init()
{
	pConnection->setConnectHandler(EV_CB(this, GameConnection::onConnected));
	pConnection->setReadHandler(EV_CB(this, GameConnection::onRead));
	pConnection->setCloseHandler(EV_CB(this, GameConnection::onClosed));
}

void GameConnection::onConnected(Connection* con)
{
	EV_INVOKE(cbConnectHandler, this);
}

void GameConnection::onRead(Connection* con)
{
	Buffer* buff = pConnection->getBuffer();
	while(buff->bytesAvaliable() >= HEAD_LENGTH_GAME)
	{
		MSG_HEAD_GAME head;
		buff->readBytes(&bufRead, 0, HEAD_LENGTH_GAME);
		read_head_game(bufRead.data(), &head);
		if (head.length < 0 || head.length > MAX_MSG_LENGTH)
		{
			Log::debug("game been closed due to illegal head length: %d", head.length);
			pConnection->close();
		}
		buff->tight();
		bufRead.clear();
		if (buff->bytesAvaliable() >= head.length)
		{
			buff->readBytes(&bufRead, 0, head.length);
			EV_INVOKE(cbMessageHandler, this, &head, bufRead.data());
			buff->tight();
			bufRead.clear();
		}
	}
}

void GameConnection::onClosed(Connection* con)
{
	EV_INVOKE(cbCloseHandler, this);
}

void GameConnection::connect(const char* host, short port)
{
	pConnection->connect(host, port);
}

void GameConnection::send(char* head, size_t head_len, char* body, size_t body_len)
{

}

void GameConnection::send(char* data, size_t size)
{
	pConnection->send(data, size);
}

void GameConnection::setMessageHandler(const MessageHandler &cb)
{
	cbMessageHandler = cb;
}

void GameConnection::setCloseHandler(const EventHandler &cb)
{
	cbCloseHandler = cb;
}

void GameConnection::setConnectHandler(const EventHandler &cb)
{
	cbConnectHandler = cb;
}

GameConnection::~GameConnection()
{

}

GameConnection* GameConnection::create(EventLoop* loop)
{
	Connection* con = new Connection(loop);
	con->createTcp(loop);
	GameConnection* gCon = new GameConnection(con);
	return gCon;
}


GameConnection* GameConnection::create(EventLoop* loop, int fd /*= INVALID_SOCKET*/)
{
	GameConnection* gCon = new GameConnection(loop,fd);
	return gCon;
}

void GameConnection::destory(GameConnection* con)
{
	delete con;
}
