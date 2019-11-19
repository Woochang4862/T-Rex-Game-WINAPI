#pragma once
#include "Scene.h"
#include "Player.h"
#include "Ground1.h"
#include "Ground2.h"
#include "Obstacle.h"
#include "GameOverText.h"
#include "ReplayIcon.h"
#include "Number.h"

#define D_GAME_SPEED 10
#define D_INCREASE_GAME_SPEED 0.1f

class GameScene :
	public Scene
{
public:
	virtual void Initialize();		//모든 Scene에는 반드시 Initialize함수가 있어야합니다. (추상 클래스 참고)
public:
	bool isRunning;
	float gameSpeed;
	float score;
	Player* player;
	Ground1* ground1;
	Ground2* ground2;
	Obstacle* obstacle;
	GameOverText* gameOverText;
	ReplayIcon* replayIcon;
	Number* numbers[5];
	void Restart();
	void GameOver();
	void SetScore(float score);
	void IncreaseGameSpeed();
};
