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