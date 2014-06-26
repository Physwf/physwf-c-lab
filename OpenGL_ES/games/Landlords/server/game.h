#ifndef _GAME_H
#define _GAME_H

#include "../shared/logic.h"

extern Game game;

void init();
void onPlayerJoin(int total,int pid, PConnection connection);
void run();

#endif