#include "Master.h"
#include "Message.h"

Master::Master()
{

}

Master::~Master()
{

}

void Master::start()
{
	pLoop = new EventLoop();
	pGateWay = new Connection(pLoop);
	pGateWay->setConnectHandler(EV_CB(this,Master::onGateWayConnected));
	pGateWay->setReadHandler(EV_CB(this, Master::onGateWayMessage));
	//pGateWay->connect();
}

void Master::run()
{
	while (true)
	{
		pLoop->run();
	}
}

void Master::onGateWayConnected(void* data)
{

}

void Master::onGateWayMessage(void* data)
{
	Buffer* gBuffer = pGateWay->getBuffer();
	if (gBuffer->bytesAvaliable() > HEAD_LENGTH)
	{
		MSG_HEAD head;
		read_head(pBuffer.data(), &head);
		if (gBuffer->bytesAvaliable() >= head.length)
		{
			//gBuffer->seek(2);
			gBuffer->readBytes(&pBuffer, 2, head.length);
			//call msg handler
			pBuffer.clear();
		}
	}
}