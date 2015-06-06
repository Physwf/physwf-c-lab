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

void Player::joinGame(gid_t which)
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
