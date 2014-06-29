#include "../shared/msg.h"
#include "net.h"

void send_data(unsigned short mid,char* data, int len)
{
	MsgHead head;
	head.msgid = mid;
	head.length = len;
	send(conn.socket, (char*)&head, sizeof(MsgHead), 0);
	send(conn.socket, data, len, 0);
}

void send_start_game()
{
	MSG_SUBM_START_GAME msg;
	send_data(MSG_SUBM_START_GAME_1003,(char*)&msg, sizeof(MSG_SUBM_START_GAME));
}

void send_loot_socre(unsigned short score)
{
	MSG_NOTI_LOOT_SCORE msg;
	msg.score = score;
	send_data(MSG_SUBM_LOOT_SCORE_1006,(char*)&msg, sizeof(MSG_NOTI_LOOT_SCORE));
}

void send_play_cards()
{
	
}