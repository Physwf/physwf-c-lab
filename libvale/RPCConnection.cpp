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

void RPCConnection::call(MID mid, char* data, size_t len)
{
	MSG_HEAD head = { mid, len };
	wBuffer.append((char*)&head,HEAD_LENGTH);
	wBuffer.append(data, len);
	pConnection->send(wBuffer);
}

void RPCConnection::run()
{
	pLoop->run();
}


void RPCConnection::registerMsgHandler(MID mid, EventHandler handler)
{
	mCallbacks[mid] = handler;
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
			buff->readBytes(&rBuffer, 2, head.length);
			buff->tight();
			EV_INVOKE(mCallbacks[head.id],rBuffer.data());
			rBuffer.clear();
		}
	}
}

void RPCConnection::onClose()
{

}