#include "stdafx.h"
#include "Obstacle.h"
#include "InputManager.h"
#include "AnimationRenderer.h"
#include "ListAnimation.h"
#include "GameScene.h"
#include "SheetAnimation.h"
#include <cstdlib>
#include <ctime>

Obstacle::Obstacle()
	:GameObject(animRenderer = new AnimationRenderer()),
	col(*transform, Vector2(17.0f, 78.75f)),
	x(1200.0f)
{
	srand((unsigned int)time(NULL));

	ListAnimation* obstacle1 = new ListAnimation(0, 1.0f);
	obstacle1->PushBackSprite(L"resources/obstacle1.png");
	ListAnimation* obstacle2 = new ListAnimation(1, 1.0f);
	obstacle2->PushBackSprite(L"resources/obstacle2.png");
	ListAnimation* obstacle3 = new ListAnimation(2, 1.0f);
	obstacle3->PushBackSprite(L"resources/obstacle3.png");
	ListAnimation* obstacle4 = new ListAnimation(3, 1.0f);
	obstacle4->PushBackSprite(L"resources/obstacle4.png");
	SheetAnimation* obstacle5 = new SheetAnimation(4, 2.0f, L"resources/bird.png", 91, 80, 2);
	
	animRenderer->PushBackAnimation(obstacle1);
	animRenderer->PushBackAnimation(obstacle2);
	animRenderer->PushBackAnimation(obstacle3);
	animRenderer->PushBackAnimation(obstacle4);
	animRenderer->PushBackAnimation(obstacle5);

	transform->SetPosition(1200.0f, 500.0f);
}


void Obstacle::Update()
{
	if (((GameScene&)Scene::GetCurrentScene()).isRunning) Move();
}

void Obstacle::Move()
{
	x += GetGameScene().gameSpeed;
	transform->position.x = 1200.0f - x;
	if (x >= 1200.0f) {
		x = 0.0f;
		transform->position.x = 1200.0f;
		GetGameScene().IncreaseGameSpeed();

		int tmp;
		float y;
		switch (tmp = rand()%5)
		{
		case 0:
		case 1:
		case 2:
			col.boundingBox = Vector2(15.0f, 78.75f);
			y = 500.0f;
			break;
		case 3:
			col.boundingBox = Vector2(85.0f, 85.0f);
			y = 500.0f;
			break;
		case 4:
			y = (rand() % 2) ? 400.0f : 450.0f;
			col.boundingBox = Vector2(71.0f, 50.0f);
			break;
		}
		printf("%d번 장애물\n", tmp);
		printf("장애물 위치 : %g\n", transform->position.y = y);
		animRenderer->ChangeAnimation(tmp);
	}
}

GameScene& Obstacle::GetGameScene()
{
	return (GameScene&)Scene::GetCurrentScene();
}