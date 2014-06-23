#include "../shared/logic.h"
#include "../shared/common.h"

void init_service();

void broadcast_deal_result(PDealResult result);
void send_wait_for_loot(int who);
void broadcast_loot_score(int who,int score);
void send_play_start();
