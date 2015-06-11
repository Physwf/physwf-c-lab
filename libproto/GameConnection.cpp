#include "GameConnection.h"

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
	if (buff->bytesAvaliable() > sizeof(MSG_HEAD_GAME))
	{
		MSG_HEAD_GAME head;
		read_head_game(buff->data(), &head);
		if (head.length < 0 || head.length > 512) pConnection->close();
		if (buff->bytesAvaliable() >= head.length)
		{
			//gBuffer->seek(2);
			buff->readBytes(&bufRead, 2, head.length);
			buff->tight();
			EV_INVOKE(cbMessageHandler, this, &head, bufRead.data());
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

}

void GameConnection::setMessageHandler(const EventHandler &cb)
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
