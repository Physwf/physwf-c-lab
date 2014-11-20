#ifndef _LISTENER_H
#define _LISTENER_H

#include "net.h"

typedef void (*MsgListener)(char*);

void addMsgListener(int msgid, MsgListener listener);
void listener_loop();

#endif