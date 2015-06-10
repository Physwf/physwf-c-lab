/*
#include "SyncMsgConnection.h"

template <typename TMID, typename TMSG_HEAD>
SyncMsgConnection<TMID, TMSG_HEAD>::SyncMsgConnection(EventLoop* loop, int fd)
{
	pConnection = new Connection(loop, fd);
	init();
}

template <typename TMID, typename TMSG_HEAD>
SyncMsgConnection<TMID, TMSG_HEAD>::SyncMsgConnection(Connection* conn) :pConnection(conn)
{
	init();
}

template <typename TMID, typename TMSG_HEAD>
SyncMsgConnection<TMID, TMSG_HEAD>::~SyncMsgConnection()
{
}

template <typename TMID, typename TMSG_HEAD>
void SyncMsgConnection<TMID, TMSG_HEAD>::send(char* head, size_t head_len, char* body, size_t body_len)
{
	Connection::send(head, head_len);
	Connection::send(body, body_len);
}


template <typename TMID, typename TMSG_HEAD>
void SyncMsgConnection<TMID, TMSG_HEAD>::send(char* data, size_t size)
{
	Connection::send(data, size);
}

template <typename TMID, typename TMSG_HEAD>
void SyncMsgConnection<TMID, TMSG_HEAD>::init()
{
	pConnection->setConnectHandler(EV_CB(this, SyncMsgConnection::onConnected));
	pConnection->setReadHandler(EV_CB(this, SyncMsgConnection::onSocketData));
}

template <typename TMID, typename TMSG_HEAD>
void SyncMsgConnection<TMID, TMSG_HEAD>::onConnected(Connection* con)
{
	EV_INVOKE(cbConnectHandler, this);
}

template <typename TMID, typename TMSG_HEAD>
void SyncMsgConnection<TMID, TMSG_HEAD>::onSocketData(SyncMsgConnection* conn)
{
	Buffer* buff = pConnection->getBuffer();
	if (buff->bytesAvaliable() > sizeof(TMSG_HEAD))
	{
		TMSG_HEAD head;
		//read_head_back(buff->data(), &head);
		if (head.length < 0 || head.length > 512) pConnection->close();
		if (buff->bytesAvaliable() >= head.length)
		{
			//gBuffer->seek(2);
			buff->readBytes(&bufRead, 2, head.length);
			buff->tight();
			EV_INVOKE(onMessage, this, &head,bufRead.data());
			bufRead.clear();
		}
	}
}

template <typename TMID, typename TMSG_HEAD>
void SyncMsgConnection<TMID, TMSG_HEAD>::onClose()
{

}

template <typename TMID, typename TMSG_HEAD>
SyncMsgConnection<TMID, TMSG_HEAD>* SyncMsgConnection<TMID, TMSG_HEAD>::create(EventLoop* loop)
{
	Connection* conn = new Connection(loop);
	conn->createTcp(loop);
	return new SyncMsgConnection(conn);
}
#include "Message.h"
EXPIMP_TEMPLATE template class VALE_DLL SyncMsgConnection<mid_t, MSG_HEAD_GATE>;
EXPIMP_TEMPLATE template class VALE_DLL SyncMsgConnection<mid_t, MSG_HEAD_BACK>;
EXPIMP_TEMPLATE template class VALE_DLL SyncMsgConnection<mid_t, MSG_HEAD_GAME>;
*/