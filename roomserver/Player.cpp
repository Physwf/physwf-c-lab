#include "Player.h"

Player::Player()
{

}


Player::~Player()
{

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

}
