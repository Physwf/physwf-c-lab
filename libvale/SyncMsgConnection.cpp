#include "SyncMsgConnection.h"

template <typename mid, typename MSG_HEAD>
SyncMsgConnection<mid, MSG_HEAD>::SyncMsgConnection(EventLoop* loop) :Connection(loop)
{
	Connection::setReadHandler(EV_CB(this, SyncMsgConnection<mid, MSG_HEAD>::onSocketData));
}

template <typename mid, typename MSG_HEAD>
SyncMsgConnection<mid, MSG_HEAD>::~SyncMsgConnection()
{
}

template <typename mid, typename MSG_HEAD>
void SyncMsgConnection<mid, MSG_HEAD>::send(char* head, size_t head_len, char* body, size_t body_len)
{
	Connection::send(head, head_len);
	Connection::send(body, body_len);
}

template <typename mid, typename MSG_HEAD>
void SyncMsgConnection<mid, MSG_HEAD>::registerMsgHandler(mid_t mid, EventHandler handler)
{
	mCallbacks[mid] = handler;
}

template <typename mid, typename MSG_HEAD>
void SyncMsgConnection<mid, MSG_HEAD>::onConnected()
{

}

template <typename mid, typename MSG_HEAD>
void SyncMsgConnection<mid, MSG_HEAD>::onSocketData()
{
	Buffer* buff = getBuffer();
	if (buff->bytesAvaliable() > sizeof(MSG_HEAD))
	{
		MSG_HEAD head;
		read_head(buff->data(), &head);
		if (buff->bytesAvaliable() >= head.length)
		{
			//gBuffer->seek(2);
			buff->readBytes(&bufRead, 2, head.length);
			buff->tight();
			EV_INVOKE(mCallbacks[head.id], &head, bufRead.data());
			bufRead.clear();
		}
	}
}

template <typename mid, typename MSG_HEAD>
void SyncMsgConnection<mid, MSG_HEAD>::onClose()
{

}