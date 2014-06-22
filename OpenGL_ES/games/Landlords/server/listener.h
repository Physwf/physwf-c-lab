#ifndef _MSG_H
#define _MSG_H

#include "msg.h"
#include <queue>
#include <map>

typedef void (*MsgListener)(char*);

void addMsgListener(int msgid, MsgListener listener);
void listener_loop();
void onPlayerJoin(int total,int pid);

#endif