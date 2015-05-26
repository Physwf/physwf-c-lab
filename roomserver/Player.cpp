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
