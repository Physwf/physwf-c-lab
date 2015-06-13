#include "ClientConnection.h"

ClientConnection::ClientConnection(EventLoop* loop, int fd /*= INVALID_SOCKET*/)
{
	pConnection = new Connection(loop, fd);
	init();
}

ClientConnection::ClientConnection(Connection* con) :pConnection(con)
{
	init();
}

void ClientConnection::init()
{
	pConnection->setConnectHandler(EV_CB(this, ClientConnection::onConnected));
	pConnection->setReadHandler(EV_CB(this, ClientConnection::onRead));
	pConnection->setCloseHandler(EV_CB(this, ClientConnection::onClosed));
}

void ClientConnection::onConnected(Connection* con)
{
	EV_INVOKE(cbConnectHandler, this);
}

void ClientConnection::onRead(Connection* con)
{
	Buffer* buff = pConnection->getBuffer();
	if (buff->bytesAvaliable() > sizeof(MSG_HEAD_GATE))
	{
		MSG_HEAD_GATE head;
		read_head_gate(buff->data(), &head);
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

void ClientConnection::onClosed(Connection* con)
{
	EV_INVOKE(cbCloseHandler, this);
}

void ClientConnection::connect(const char* host, short port)
{
	pConnection->connect(host, port);
}

void ClientConnection::send(char* head, size_t head_len, char* body, size_t body_len)
{

}

void ClientConnection::send(char* data, size_t size)
{
	pConnection->send(data, size);
}

void ClientConnection::setMessageHandler(const MessageHandler &cb)
{
	cbMessageHandler = cb;
}

void ClientConnection::setCloseHandler(const EventHandler &cb)
{
	cbCloseHandler = cb;
}

void ClientConnection::setConnectHandler(const EventHandler &cb)
{
	cbConnectHandler = cb;
}

ClientConnection::~ClientConnection()
{

}

ClientConnection* ClientConnection::create(EventLoop* loop)
{
	Connection* con = new Connection(loop);
	con->createTcp(loop);
	ClientConnection* gCon = new ClientConnection(con);
	return gCon;
}


ClientConnection* ClientConnection::create(EventLoop* loop, int fd /*= INVALID_SOCKET*/)
{
	ClientConnection* con = new ClientConnection(loop,fd);
	return con;
}

void ClientConnection::destory(ClientConnection* con)
{
	delete con;
}

