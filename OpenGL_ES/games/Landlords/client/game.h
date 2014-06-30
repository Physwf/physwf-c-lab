#include "../shared/logic.h"

#define GAME_PHASE_WAIT_FOR_OTHERS 	0
#define GAME_PHASE_WAIT_FOR_PLAYERS 1
#define GAME_PHASE_WAIT_FOR_LOOT 	2
#define GAME_PHASE_WAIT_FOR_CARDS	3

extern Game game;

void init();
void run();