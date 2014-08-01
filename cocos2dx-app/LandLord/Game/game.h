
#ifndef _GAME_H
#define _GAME_H

#include "../shared/logic.h"
#include "LLSceneController.h"

#define GAME_PHASE_WAIT_FOR_OTHERS 	0
#define GAME_PHASE_WAIT_FOR_PLAYERS 1
#define GAME_PHASE_WAIT_FOR_LOOT 	2
#define GAME_PHASE_WAIT_FOR_CARDS	3

extern Game game;

void init(LLSceneController* scene);
void run();

#endif