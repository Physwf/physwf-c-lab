//#include "SyncMsgConnection.h"
//
//template <typename TMID, typename TMSG_HEAD>
//SyncMsgConnection<TMID, TMSG_HEAD>::SyncMsgConnection(EventLoop* loop, int fd) :Connection(loop,fd)
//{
//	Connection::setReadHandler(EV_CB(this, SyncMsgConnection<TMID, TMSG_HEAD>::onSocketData));
//}
//
//template <typename TMID, typename TMSG_HEAD>
//SyncMsgConnection<TMID, TMSG_HEAD>::~SyncMsgConnection()
//{
//}
//
//template <typename TMID, typename TMSG_HEAD>
//void SyncMsgConnection<TMID, TMSG_HEAD>::send(char* head, size_t head_len, char* body, size_t body_len)
//{
//	Connection::send(head, head_len);
//	Connection::send(body, body_len);
//}
//
//
//template <typename TMID, typename TMSG_HEAD>
//void SyncMsgConnection<TMID, TMSG_HEAD>::send(char* data, size_t size)
//{
//	Connection::send(data, size);
//}
//
//
//template <typename TMID, typename TMSG_HEAD>
//void SyncMsgConnection<TMID, TMSG_HEAD>::onConnected()
//{
//
//}
//
//template <typename TMID, typename TMSG_HEAD>
//void SyncMsgConnection<TMID, TMSG_HEAD>::onSocketData(SyncMsgConnection* conn)
//{
//	Buffer* buff = getBuffer();
//	if (buff->bytesAvaliable() > sizeof(TMSG_HEAD))
//	{
//		TMSG_HEAD head;
//		read_head_back(buff->data(), &head);
//		if (head.length < 0 || head.length > 512) close();
//		if (buff->bytesAvaliable() >= head.length)
//		{
//			//gBuffer->seek(2);
//			buff->readBytes(&bufRead, 2, head.length);
//			buff->tight();
//			EV_INVOKE(onMessage, this, &head,bufRead.data());
//			bufRead.clear();
//		}
//	}
//}
//
//template <typename TMID, typename TMSG_HEAD>
//void SyncMsgConnection<TMID, TMSG_HEAD>::onClose()
//{
//
//}