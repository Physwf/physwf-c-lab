#include "Connection.h"

Connection::Connection(EventLoop* loop, int fd /*= INVALID_SOCKET*/) :pLoop(loop), sSocket(fd)
{
	if (sSocket.isValid())
	{
		pLoop->addEventListener(sSocket.getFd(), EV_IO_READ, EV_IO_CB(this, Connection::onRead), NULL);
	}
}

Connection::~Connection()
{

}

int Connection::connect(const char* host, short port)
{
	if (sSocket.connect(host, port) == SOCKET_ERROR)
	{
		return -1;
	}
	pLoop->addEventListener(sSocket.getFd(), EV_IO_ALL, EV_IO_CB(this, Connection::onConnect), NULL);

	return 0;
}

int Connection::send(const char* data, size_t size)
{
	bufWrite.append(data, size);
	if (!bWriting)
	{
		bWriting = true;
		pLoop->addEventListener(sSocket.getFd(), EV_IO_WRITE, EV_IO_CB(this,Connection::onWrite), NULL);
	}
	return 0;
}

int Connection::send(Buffer& buf)
{
	return send(buf.data(), buf.size());
}

void Connection::close()
{
	if (sSocket.isValid()) return;
	pLoop->removeEventListener(sSocket.getFd(), EV_IO_ALL);
	sSocket.close();
}

void Connection::onConnect(int fd, int event, void* data)
{
	pLoop->removeEventListener(sSocket.getFd(), EV_IO_ALL);

#ifdef WIN32
	char sockerr = 0;
	int errlen = sizeof sockerr;
#else // WIN32
	int sockerr = 0;
	socklen_t errlen = sizeof sockerr;
#endif
	if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &sockerr, &errlen) == -1)
	{
		//sockerr = GetLastError();
	}
	if (sockerr)
	{
		close();
		return;
	}
	sSocket.setNonBlock();
	pLoop->addEventListener(sSocket.getFd(), EV_IO_READ, EV_IO_CB(this, Connection::onConnect), NULL);

}

void Connection::onRead(int fd, int event, void* data)
{

}

void Connection::onWrite(int fd, int event, void* data)
{

}

void Connection::onClose()
{

}

