#include "SyncMsgConnection.h"

template <typename mid, typename MSG_HEAD>
SyncMsgConnection<mid, MSG_HEAD>::SyncMsgConnection(EventLoop* loop, int fd) :Connection(loop,fd)
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
void SyncMsgConnection<mid, MSG_HEAD>::onConnected()
{

}

template <typename mid, typename MSG_HEAD>
void SyncMsgConnection<mid, MSG_HEAD>::onSocketData(Connection* conn)
{
	Buffer* buff = getBuffer();
	if (buff->bytesAvaliable() > sizeof(MSG_HEAD))
	{
		MSG_HEAD head;
		read_head(buff->data(), &head);
		if (head.length < 0 || head.length > 512) close();
		if (buff->bytesAvaliable() >= head.length)
		{
			//gBuffer->seek(2);
			buff->readBytes(&bufRead, 2, head.length);
			buff->tight();
			EV_INVOKE(onMessage, head.id, &head, sizeof(MSG_HEAD),bufRead.data(),head.length);
			bufRead.clear();
		}
	}
}

template <typename mid, typename MSG_HEAD>
void SyncMsgConnection<mid, MSG_HEAD>::onClose()
{

}