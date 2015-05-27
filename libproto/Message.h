#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "type.h"

typedef struct s_msg_head_back
{
	unsigned short length;
	mid_t id;
} MSG_HEAD_BACK;

typedef struct s_msg_head_gate
{
	unsigned short length;
	mid_t id;
	pid_t pid;
} MSG_HEAD_GATE;


int read_head(char* buff, MSG_HEAD_BACK* head);

#endif