#include "stdafx.h"
#include "Ground2.h"
#include "GameScene.h"

Ground2::Ground2()
	:GameObject(L"resources/ground2.png")
{
	transform->SetPosition(1800.0f, 529.7f);
}

void Ground2::Update()
{
	if (GetGameScene().isRunning) {
		transform->position.x-=GetGameScene().gameSpeed;
		if (transform->position.x <= -600) {
			transform->position.x = 1800;
		}
	}
}

GameScene& Ground2::GetGameScene()
{
	return (GameScene&)Scene::GetCurrentScene();
}