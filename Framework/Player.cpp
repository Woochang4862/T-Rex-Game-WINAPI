#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "GameScene.h"
#include "AnimationRenderer.h"
#include "ListAnimation.h"
#include "SheetAnimation.h"
#include "TimeManager.h"

#define STATE_RUNNING 0
#define STATE_CRUSHED 1
#define STATE_DOWN 2
#define STATE_STOPPED 3

Player::Player()
	:GameObject(animRenderer = new AnimationRenderer()),		
	jumpPower(3.5f),
	isJumping(false),
	posY(transform->position.y),
	gravity(9.8f),
	jumpTime(0.0f),
	jumpAccell(230.0f),
	col(*transform, Vector2(80.0f, 90.0f))
{
	SheetAnimation* sanim = new SheetAnimation(STATE_RUNNING, 20.0f, L"rex.png",88,94,4);
	ListAnimation* crushedRex = new ListAnimation(STATE_CRUSHED, 1.0f);
	crushedRex->PushBackSprite(L"resources/crushed-rex.png");
	SheetAnimation* downRex = new SheetAnimation(STATE_DOWN, 20.0f, L"resources/down-rex.png", 118, 60,2);
	ListAnimation* stoppedRex = new ListAnimation(STATE_STOPPED, 1.0f);
	stoppedRex->PushBackSprite(L"resources/stopped-rex.png");
	animRenderer->PushBackAnimation(sanim);
	animRenderer->PushBackAnimation(crushedRex);
	animRenderer->PushBackAnimation(downRex);
	animRenderer->PushBackAnimation(stoppedRex);
	animRenderer->ChangeAnimation(3);
	transform->SetPosition(100.0f, 500.0f);
}

void Player::Update()
{
	if (GetGameScene().isRunning) {
		if ((InputManager::GetMyKeyState(VK_SPACE) || InputManager::GetMyKeyState(VK_UP)) && !isJumping)
		{
			isJumping = true;
			posY = transform->position.y;
		}
		if (isJumping)
		{
			Jump();
		}

		if (InputManager::GetMyKeyState(VK_DOWN) && animRenderer->currentState != STATE_DOWN && transform->position.y > 400) // 숙인 상태로 바꿔주기
		{
			animRenderer->ChangeAnimation(STATE_DOWN);
			col.boundingBox = Vector2(106.0f,60.0f);
			
		}
		else if (!InputManager::GetMyKeyState(VK_DOWN) && animRenderer->currentState != STATE_RUNNING) // 달리는 상태로 바꿔주기
		{
			animRenderer->ChangeAnimation(STATE_RUNNING);
			col.boundingBox = Vector2(80.0f, 90.0f);
			transform->position.y = 500.0f;
		}

		if(animRenderer->currentState == STATE_DOWN)
		{
			transform->position.y = 520.0f;
		}
		else if (!isJumping && animRenderer->currentState == STATE_RUNNING || animRenderer->currentState == STATE_CRUSHED)
		{
			transform->position.y = 500.0f;
		}

		if(InputManager::GetKeyUp(VK_ESCAPE)) // 게임 일시정지
		{
			animRenderer->ChangeAnimation(3); //달리기 정지 애니메이이션 
			GetGameScene().isRunning = false;
		}
		GetGameScene().SetScore(GetGameScene().score + 0.05f);
	}
	else {
		if (InputManager::GetKeyUp(VK_ESCAPE) && animRenderer->currentState == 1) // 충돌했고 게임 다시시작
		{
			animRenderer->ChangeAnimation(0);
			GetGameScene().Restart();
		}
		if (InputManager::GetKeyUp(VK_ESCAPE) && animRenderer->currentState == 3) // 충돌했고 게임 다시시작
		{
			animRenderer->ChangeAnimation(0);
			GetGameScene().isRunning = true;
		}
	}
}

void Player::LateUpdate()
{
	if (GetGameScene().isRunning){
		if (col.Intersected(enemy->col))
		{
			printf("충돌중\n");
			GetGameScene().GameOver();
			GetGameScene().isRunning = false;
			animRenderer->ChangeAnimation(1);
		}
	}
}

void Player::Jump()
{
	//y=-a*x+b에서 (a: 중력가속도, b: 초기 점프속도)
	//적분하여 y = (-a/2)*x*x + (b*x) 공식을 얻는다.(x: 점프시간, y: 오브젝트의 높이)
	//변화된 높이 height를 기존 높이 _posY에 더한다.
	float height = (jumpTime * jumpTime * (-gravity) / 2) + (jumpTime * jumpPower);
	transform->position = Vector2(transform->position.x, posY - height*jumpAccell);
	//점프시간을 증가시킨다.
	jumpTime += TimeManager::GetDeltaTime();

	//처음의 높이 보다 더 내려 갔을때 => 점프전 상태로 복귀한다.
	if (height < 0.0f)
	{
		isJumping = false;
		jumpTime = 0.0f;
		transform->position = Vector2(transform->position.x, posY);
	}
}

GameScene& Player::GetGameScene()
{
	return (GameScene&)Scene::GetCurrentScene();
}