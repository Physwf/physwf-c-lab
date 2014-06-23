#ifndef _LISTENER_H
#define _LISTENER_H

#include "../shared/msg.h"
#include <queue>
#include <map>

typedef void (*MsgListener)(char*);

void addMsgListener(int msgid, MsgListener listener);
void listener_loop();
void onPlayerJoin(int total,int pid);

#endif