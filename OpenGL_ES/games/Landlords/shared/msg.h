#ifndef _MSG_H
#define _MSG_H

#include "logic.h"

#define HEAD_LENGTH  8

enum
{
	MSG_NOTI_ASK_WAIT_MORE_1000=1000,
	MSG_NOTI_PLAYER_JOIN_1001
	MSG_NOTI_HOST_WAIT_PLAYERS_1002,
	MSG_SUBM_START_GAME_1003,
	MSG_NOTI_DEAL_RESULT_1004,
	MSG_NOTI_WAIT_LOOT_1005,
	MSG_SUBM_LOOT_SCORE_1006
};

typedef struct msg_head_t
{
	unsigned short msgid;
	unsigned int length;
} MsgHead, *PMsgHead;

typedef struct msg_ask_wait_more_t
{
	//empty
}
MSG_ASK_WAIT_MORE,*PMSG_ASK_WAIT_MORE;

typedef struct msg_noti_player_join_t
{
	int playerId;
}
MSG_NOTI_PLAYER_JOIN,*PMSG_NOTI_PLAYER_JOIN;

typedef struct msg_noti_host_wait_players_t
{
}
MSG_NOTI_HOST_WAIT_PLAYERS,*PMSG_NOTI_HOST_WAIT_PLAYERS;

typedef struct msg_subm_start_game_t
{
	//empty
}
MSG_SUBM_START_GAME,*PMSG_SUBM_START_GAME;

typedef struct msg_noti_deal_result_t
{
	DealResult result;
}
MSG_NOTI_DEAL_RESULT, *PMSG_NOTI_DEAL_RESULT;

typedef struct msg_noti_wait_loot_t
{
	unsigned int who;
} 
MSG_NOTI_WAIT_LOOT,*PMSG_NOTI_WAIT_LOOT;

typedef struct msg_subm_loot_score_t
{
	unsigned int who;
	unsigned short score;
}
MSG_SUBM_LOOT_SCORE,*PMSG_SUBM_LOOT_SCORE;

#endif