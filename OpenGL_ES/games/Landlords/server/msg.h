#include "game.h"

#define HEAD_LENGTH  (sizeof(short) + sizeof(int))

enum
{
	MSG_BRDCST_DEAL_RESULT_1000=1000,
	MSG_SRV_WAIT_LOOT_1001,
	MSG_CLNT_LOOT_SCORE_1002
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
MSG_BRDCST_DEAL_RESULT, *PMSG_BRDCST_DEAL_RESULT;

typedef struct msg_srv_wait_loot_t
{
	unsigned int who;
} 
MSG_SRV_WAIT_LOOT,*PMSG_SRV_WAIT_LOOT;

typedef struct msg_clnt_loot_score_t
{
	unsigned int who;
	unsigned short score;
}
MSG_CLNT_LOOT_SCORE,*PMSG_CLNT_LOOT_SCORE;