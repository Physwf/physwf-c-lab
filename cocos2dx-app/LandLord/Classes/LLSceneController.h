#ifndef _LLSCENECONTROLLER_H
#define _LLSCENECONTROLLER_H



class LLSceneController
{
public:
	LLSceneController();
	~LLSceneController();

	void showWaitForMorePlayers();
	void showPlayerJoin();
	void showDealResult();
	void showLootScore();
	void showLootResult();
	void showPlayCards();
	void showGameOver();
};

#endif