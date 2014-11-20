#include "../shared/logic.h"
#include "../shared/common.h"

void init_service();

void send_ask_wait_more(int pid);
void send_player_joined(int pid, int who);
void send_host_waiting_players(int pid);
void send_deal_result(int who, PDealResult result);
void send_wait_for_loot(int who);
void broadcast_loot_score(int who,int score);
void send_wait_cards();
void broadcast_play_cards();

