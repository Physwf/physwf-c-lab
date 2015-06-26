#include "Player.h"

Player::Player()
{

}


Player::~Player()
{

}


void Player::init()
{
	nId = 0;	nRid = 0;
	nTid = 0;	nCid = 0;
	nSid = 0;	nStatus = 0;
}

void Player::enterRoom(rid_t which)
{
	setRoomId(which);
}

void Player::leaveRoom()
{

}

void Player::joinGame(tid_t which)
{
	setTableId(which);
}

void Player::leaveGame()
{

}

void Player::setGate(ServiceConnection* gate)
{
	pGate = gate;
}

void Player::send(MSG_HEAD_BACK* head, char* body)
{
	char buffer[32] = { 0 };
	int size = pack_back_msg2(buffer, head, body);
	pGate->send(buffer, size);
}
