#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "Ground1.h"
#include "Ground2.h"
#include "GameOverText.h"
#include "ReplayIcon.h"
#include "Number.h"

void GameScene::Initialize()
{
	isRunning = false;

	gameSpeed = D_GAME_SPEED;

	score = 0;

	gameOverText = (GameOverText*)PushBackGameObject(new GameOverText());

	replayIcon = (ReplayIcon*)PushBackGameObject(new ReplayIcon());

	//5자리까지 표현
	numbers[0] = (Number*)PushBackGameObject(new Number());
	numbers[0]->transform->SetPosition(1160, 35);

	numbers[1] = (Number*)PushBackGameObject(new Number());
	numbers[1]->transform->SetPosition(1130, 35);
	
	numbers[2] = (Number*)PushBackGameObject(new Number());
	numbers[2]->transform->SetPosition(1100, 35);

	numbers[3] = (Number*)PushBackGameObject(new Number());
	numbers[3]->transform->SetPosition(1070, 35);

	numbers[4] = (Number*)PushBackGameObject(new Number());
	numbers[4]->transform->SetPosition(1040, 35);

	ground1 = (Ground1*)PushBackGameObject(new Ground1());

	ground2 = (Ground2*)PushBackGameObject(new Ground2());

	obstacle = (Obstacle*)PushBackGameObject(new Obstacle());
	
	player = (Player*)PushBackGameObject(new Player());

	player->enemy = obstacle;

	obstacle->player = player;
}

void GameScene::Restart()
{
	gameSpeed = D_GAME_SPEED;
	SetScore(score = 0);
	gameOverText->transform->SetScale(0.0f, 0.0f);
	replayIcon->transform->SetScale(0.0f, 0.0f);
	obstacle->x = 0;
	obstacle->transform->position.x= 1200.0f;
	ground1->transform->SetPosition(600.0f, 540.0f);
	ground2->transform->SetPosition(1800.0f, 529.7f);
	isRunning = true;
}

void GameScene::GameOver()
{
	gameOverText->transform->SetScale(1.0f, 1.0f);
	replayIcon->transform->SetScale(0.7f, 0.7f);
}

void GameScene::SetScore(float score)
{
	this->score = score;
	int tmp = (int)score;
	for (int i = 0; i < 5; i++,tmp/=10) {
		numbers[i]->SetNumber(tmp % 10);
	}
}

void GameScene::IncreaseGameSpeed()
{
	gameSpeed += D_INCREASE_GAME_SPEED;
}
