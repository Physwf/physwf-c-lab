#include "SyncMsgConnection.h"
#include "Message.h"

SyncMsgConnection::SyncMsgConnection(EventLoop* loop)
{
	pLoop = loop;
	pConnection = new Connection(pLoop);
}

SyncMsgConnection::~SyncMsgConnection()
{
	delete pConnection;
}

void SyncMsgConnection::connect(const char* host, short port)
{
	pConnection->setConnectHandler(EV_CB(this, SyncMsgConnection::onConnected));
	pConnection->setReadHandler(EV_CB(this, SyncMsgConnection::onSocketData));
	pConnection->setCloseHandler(EV_CB(this, SyncMsgConnection::onClose));
	pConnection->connect(host, port);
}

void SyncMsgConnection::send(mid_t mid, char* data, size_t len)
{
	MSG_HEAD head = { mid, len };
	wBuffer.append((char*)&head,HEAD_LENGTH);
	wBuffer.append(data, len);
	pConnection->send(wBuffer);
}

void SyncMsgConnection::registerMsgHandler(mid_t mid, EventHandler handler)
{
	mCallbacks[mid] = handler;
}

void SyncMsgConnection::onConnected()
{

}

void SyncMsgConnection::onSocketData()
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

void SyncMsgConnection::onClose()
{

}