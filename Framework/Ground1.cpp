#include "stdafx.h"
#include "Ground1.h"
#include "GameScene.h"

Ground1::Ground1()
	:GameObject(L"resources/ground1.png")
{
	transform->SetPosition(600.0f, 540.0f);
}

void Ground1::Update()
{
	if(GetGameScene().isRunning){
		transform->position.x-=GetGameScene().gameSpeed;
		if (transform->position.x <= -600) {
			transform->position.x = 1800;
		}
	}
}

GameScene& Ground1::GetGameScene()
{
	return (GameScene&)Scene::GetCurrentScene();
}

