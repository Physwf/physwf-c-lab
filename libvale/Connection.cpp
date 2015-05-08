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
	//to do??
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
	//sSocket.setNonBlock();
	sSocket.setNonDelay();
	sSocket.setKeepAlive();

	pLoop->addEventListener(sSocket.getFd(), EV_IO_READ, EV_IO_CB(this, Connection::onConnect), NULL);
	EV_INVOKE(cbConnectHandler, this);
}

void Connection::onRead(int fd, int event, void* data)
{
	char buff[1024];
	int n = sSocket.read(buff, 1024);
	if(n == SOCKET_ERROR)
	{
		close();
	}
	else if (n > 0)
	{
		bufRead.append(buff, n);
		EV_INVOKE(cbReadHandler, this);
	}
}

void Connection::onWrite(int fd, int event, void* data)
{
	char* buf = bufWrite.data();
	size_t size = bufWrite.size();
	int n = sSocket.write(buf, size);
	if (n == SOCKET_ERROR)
	{
		close();
	}
	else
	{
		int avalible = bufWrite.seek(n);
		if (avalible <= 0)
		{
			bWriting = false;
			pLoop->removeEventListener(sSocket.getFd(), EV_IO_WRITE);
			EV_INVOKE(cbWriteCompleteHandler, this);
		}
	}
}

void Connection::onClose()
{
	EV_INVOKE(cbCloseHandler, this);
}

