#include "Router.h"
#include "Protocol.h"


Router::Router(ServiceConnection* service) :pMaster(service)
{
	pBuffer = new Buffer(1024 * 1024);
}

Router::~Router()
{

}

void Router::addClientForRoute(ClientConnection* client)
{
	client->setMessageHandler(EV_CB(this, Router::doRoute));
}

void Router::addServiceForRoute(ServiceConnection* service)
{

}

void Router::doRoute(mid_t mid, char* head, size_t hsize, char* body, size_t bsize)
{
	//pBuffer->append(head, hsize);
	//pBuffer->append(body, bsize);
	//
	pMaster->send(head, hsize, body, bsize);
	//pMaster->send(pBuffer->data(), pBuffer->bytesAvaliable());
	//pMaster->send();
}

