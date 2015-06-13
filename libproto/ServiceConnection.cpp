#include "ServiceConnection.h"

ServiceConnection::ServiceConnection(EventLoop* loop, int fd /*= INVALID_SOCKET*/)
{
	pConnection = new Connection(loop, fd);
	init();
}

ServiceConnection::ServiceConnection(Connection* con) :pConnection(con)
{
	init();
}

void ServiceConnection::init()
{
	EV_CB_INIT(cbConnectHandler);
	EV_CB_INIT(cbMessageHandler);
	EV_CB_INIT(cbCloseHandler);
	pConnection->setConnectHandler(EV_CB(this, ServiceConnection::onConnected));
	pConnection->setReadHandler(EV_CB(this, ServiceConnection::onRead));
	pConnection->setCloseHandler(EV_CB(this, ServiceConnection::onClosed));
}

void ServiceConnection::onConnected(Connection* con)
{
	EV_INVOKE(cbConnectHandler, this);
}

void ServiceConnection::onRead(Connection* con)
{
	Buffer* buff = pConnection->getBuffer();
	if (buff->bytesAvaliable() > sizeof(MSG_HEAD_BACK))
	{
		MSG_HEAD_BACK head;
		read_head_back(buff->data(), &head);
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

void ServiceConnection::onClosed(Connection* con)
{
	EV_INVOKE(cbCloseHandler, this);
}

void ServiceConnection::connect(const char* host, short port)
{
	pConnection->connect(host, port);
}

void ServiceConnection::send(char* head, size_t head_len, char* body, size_t body_len)
{

}

void ServiceConnection::send(char* data, size_t size)
{

}

void ServiceConnection::setMessageHandler(const MessageHandler &cb)
{
	cbMessageHandler = cb;
}

void ServiceConnection::setCloseHandler(const EventHandler &cb)
{
	cbCloseHandler = cb;
}

void ServiceConnection::setConnectHandler(const EventHandler &cb)
{
	cbConnectHandler = cb;
}

void ServiceConnection::setTest(int i)
{
	nTest = i;
}

ServiceConnection::~ServiceConnection()
{

}

ServiceConnection* ServiceConnection::create(EventLoop* loop)
{
	Connection* con = new Connection(loop);
	con->createTcp(loop);
	ServiceConnection* gCon = new ServiceConnection(con);
	return gCon;
}


ServiceConnection* ServiceConnection::create(EventLoop* loop, int fd /*= INVALID_SOCKET*/)
{
	ServiceConnection* sCon = new ServiceConnection(loop,fd);
	return sCon;
}

void ServiceConnection::destroy(ServiceConnection* con)
{
	delete con;
}

