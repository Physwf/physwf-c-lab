#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "type.h"



typedef struct s_msg_head
{
	unsigned short length;
	mid_t id;
} MSG_HEAD_ROOM;

int read_head(char* buff, MSG_HEAD_ROOM* head);

#endif