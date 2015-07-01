#include "Seat.h"
#include "Protocol.h"

Seat::Seat()
{

}

Seat::Seat(sid_t id)
{
	nSid = id;
}

Seat::~Seat()
{

}

void Seat::handleGameMessage(MSG_HEAD_GAME* head, char* body)
{
	if ((head->type & MSG_TYPE_BROADCAST) && (head->type & CHANEL_TYPE_SEAT))
	{
		MSG_HEAD_BACK hBack;
		hBack.id = head->id;
		hBack.type = head->type;
		hBack.pid = head->pid;
		hBack.rid = head->rid;
		hBack.tid = head->tid;
		hBack.id = head->id;
		hBack.length = head->length;
		broadcast(&hBack, body);
	}
}

err_t Seat::enterPlayer(Player* player)
{
	err_t err = 0;

	Player* old = findPlayer(player->pid());
	if (old)
	{
		removePlayer(player->pid());
		addPlayer(player->pid(), player);
	}
	else
	{
		player->setSeatId(nSid);
		addPlayer(player->pid(), player);
	}

	if (mPlayers.empty()) player->setStatus(STATUS_SIT);
	else player->setStatus(STATUS_STAND);
	return err;
}

err_t Seat::leavePlayer(Player* player)
{
	Player* old = removePlayer(player->pid());
	err_t err = 0;
	if (!old)
	{
		err = MSG_ERR_NOT_IN_SEAT_1009;
	}
	else
	{
		player->setSeatId(0);
		player->setStatus(0);
	}
	return err;
}

sid_t Seat::sid()
{
	return nSid;
}

