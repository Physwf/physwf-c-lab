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
		hBack.pid = pHost->pid();
		hBack.err = head->err;
		pHost->send(&hBack, body);
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

	if (mPlayers.size() == 1)
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
	err_t err = 0;
	if (pHost != NULL)
	{
		err = MSG_ERR_SEAT_BEEN_TAKEN_1012;
	}
	else
	{
		err = enterPlayer(player);
		if (!err)
		{
			pHost = player;
			player->setStatus(STATUS_SIT);
			return err;
		}
	}
	return err;
}

err_t Seat::stand(Player* player)
{
	err_t err = 0;
	if (pHost == player)
	{
		player->setStatus(STATUS_STAND);
		pHost = NULL;
	}
	else
	{
		err = 1;
	}
	return err;
}

sid_t Seat::sid()
{
	return nSid;
}

