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
	pGateWay = new RPCConnection();
	//pGateWay->connect();
}

void Master::run()
{
	pGateWay->run();
}
