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

		if (InputManager::GetMyKeyState(VK_DOWN) && animRenderer->currentState != STATE_DOWN && transform->position.y > 400) // ���� ���·� �ٲ��ֱ�
		{
			animRenderer->ChangeAnimation(STATE_DOWN);
			col.boundingBox = Vector2(106.0f,60.0f);
			
		}
		else if (!InputManager::GetMyKeyState(VK_DOWN) && animRenderer->currentState != STATE_RUNNING) // �޸��� ���·� �ٲ��ֱ�
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

		if(InputManager::GetKeyUp(VK_ESCAPE)) // ���� �Ͻ�����
		{
			animRenderer->ChangeAnimation(3); //�޸��� ���� �ִϸ����̼� 
			GetGameScene().isRunning = false;
		}
		GetGameScene().SetScore(GetGameScene().score + 0.05f);
	}
	else {
		if (InputManager::GetKeyUp(VK_ESCAPE) && animRenderer->currentState == 1) // �浹�߰� ���� �ٽý���
		{
			animRenderer->ChangeAnimation(0);
			GetGameScene().Restart();
		}
		if (InputManager::GetKeyUp(VK_ESCAPE) && animRenderer->currentState == 3) // �浹�߰� ���� �ٽý���
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
			printf("�浹��\n");
			GetGameScene().GameOver();
			GetGameScene().isRunning = false;
			animRenderer->ChangeAnimation(1);
		}
	}
}

void Player::Jump()
{
	//y=-a*x+b���� (a: �߷°��ӵ�, b: �ʱ� �����ӵ�)
	//�����Ͽ� y = (-a/2)*x*x + (b*x) ������ ��´�.(x: �����ð�, y: ������Ʈ�� ����)
	//��ȭ�� ���� height�� ���� ���� _posY�� ���Ѵ�.
	float height = (jumpTime * jumpTime * (-gravity) / 2) + (jumpTime * jumpPower);
	transform->position = Vector2(transform->position.x, posY - height*jumpAccell);
	//�����ð��� ������Ų��.
	jumpTime += TimeManager::GetDeltaTime();

	//ó���� ���� ���� �� ���� ������ => ������ ���·� �����Ѵ�.
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