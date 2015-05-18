#ifndef _MESSAGE_H
#define _MESSAGE_H

#define HEAD_LENGTH 2

#define MID unsigned int

typedef struct meg_head
{
	unsigned short length;
	MID id;
}MSG_HEAD;

int read_head(char* buff, MSG_HEAD* head);

#endif