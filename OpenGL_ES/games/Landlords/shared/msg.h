#ifndef _MSG_H
#define _MSG_H

#include "logic.h"

#define HEAD_LENGTH  8

enum
{
	MSG_NOTI_DEAL_RESULT_1000=1000,
	MSG_NOTI_WAIT_LOOT_1001,
	MSG_SUBM_LOOT_SCORE_1002
};

typedef struct msg_head_t
{
	unsigned short msgid;
	unsigned int length;
} MsgHead, *PMsgHead;

typedef struct msg_brdcst_deal_result_t
{
	DealResult result;
}
MSG_NOTI_DEAL_RESULT, *PMSG_NOTI_DEAL_RESULT;

typedef struct msg_srv_wait_loot_t
{
	unsigned int who;
} 
MSG_NOTI_WAIT_LOOT,*PMSG_NOTI_WAIT_LOOT;

typedef struct msg_clnt_loot_score_t
{
	unsigned int who;
	unsigned short score;
}
MSG_SUBM_LOOT_SCORE,*PMSG_SUBM_LOOT_SCORE;

#endif