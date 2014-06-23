#include "../shared/connection.h"
#include "../shared/common.h"

#define MAX_CONN 3

extern Connection clients[MAX_CONN];
void net_init();
void net_run();