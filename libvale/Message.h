#ifndef _MESSAGE_H
#define _MESSAGE_H

#define HEAD_LENGTH 2

typedef unsigned int mid_t;

typedef struct meg_head
{
	unsigned short length;
	mid_t id;
}MSG_HEAD;

int read_head(char* buff, MSG_HEAD* head);

#endif