#include "message.h"
#include <queue>
#include <map>

typedef void (*MsgListener)(MsgBase*);

void addMsgListener(int msgid, MsgListener listener);
void listener_loop();