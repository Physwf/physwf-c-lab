#ifndef _NET_H
#define _NET_H

#include "../shared/connection.h"

extern Connection conn;

void net_init();
void net_read();
void net_end();

#endif