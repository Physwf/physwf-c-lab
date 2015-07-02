#include "Seat.h"
#include "Protocol.h"

Seat::Seat()
{

}

Seat::Seat(sid_t id)
{
	nSid = id;
	pHost = NULL;
}

Seat::~Seat()
{

}

void Seat::handleBroadcast(MSG_HEAD_GAME* head, char* body)
{
	if ((head->type & MSG_TYPE_BROADCAST) && (head->type & CHANEL_TYPE_SEAT))
	{
		MSG_HEAD_BACK hBack;
		hBack.id = head->id;
		hBack.type = head->type;
		hBack.id = head->id;
		hBack.length = head->length;
		broadcast(&hBack, body);
	}
}

void Seat::handlePlayerMessage(MSG_HEAD_GAME* head, char* body)
{
	if (pHost)
	{
		MSG_HEAD_BACK hBack;
		hBack.id = head->id;
		hBack.type = head->type;
		hBack.id = head->id;
		hBack.length = head->length;
		pHost->send(&hBack, body);
	}
}

err_t Seat::enterPlayer(Player* player)
{
	err_t err = 0;

	Player* old = findPlayer(player->pid());
	if (old != player)
	{
		removePlayer(player->pid());
		addPlayer(player->pid(), player);
	}
	else
	{
		player->setSeatId(nSid);
		addPlayer(player->pid(), player);
	}

	if (mPlayers.empty())
	{
		player->setStatus(STATUS_SIT);
		pHost = player;
	}
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
		if (player == pHost) pHost = NULL;
	}
	return err;
}

err_t Seat::take(Player* player)
{
	if (pHost != NULL)
	{
		return MSG_ERR_SEAT_BEEN_TAKEN_1012;
	}
	else
	{
		if (enterPlayer(player) == 0)
		{
			pHost = player;
			player->setStatus(STATUS_SIT);
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

err_t Seat::stand(Player* player)
{
	if (player->getStatus() == STATUS_STAND)
	{

	}
}

sid_t Seat::sid()
{
	return nSid;
}

