#include "RPCConnection.h"
#include "Message.h"

RPCConnection::RPCConnection()
{
	pLoop = new EventLoop();
	pConnection = new Connection(pLoop);
}

RPCConnection::~RPCConnection()
{
	delete pLoop;
	delete pConnection;
}

void RPCConnection::connect(const char* host, short port)
{
	pConnection->setConnectHandler(EV_CB(this, RPCConnection::onConnected));
	pConnection->setReadHandler(EV_CB(this, RPCConnection::onSocketData));
	pConnection->setCloseHandler(EV_CB(this, RPCConnection::onClose));
	pConnection->connect(host, port);
}

void RPCConnection::call()
{

}

void RPCConnection::run()
{
	pLoop->run();
}

void RPCConnection::onConnected()
{

}

void RPCConnection::onSocketData()
{
	Buffer* buff = pConnection->getBuffer();
	if (buff->bytesAvaliable() > HEAD_LENGTH)
	{
		MSG_HEAD head;
		read_head(buff->data(), &head);
		if (buff->bytesAvaliable() >= head.length)
		{
			//gBuffer->seek(2);
			buff->readBytes(&bBuffer, 2, head.length);
			buff->tight();
			//call msg handler
			bBuffer.clear();
		}
	}
}

void RPCConnection::onClose()
{

}