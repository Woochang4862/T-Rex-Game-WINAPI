#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
#include "AnimationRenderer.h"

class Obstacle :
	public GameObject
{
public:
	Obstacle();
public:
	float x;

	AABBCollider col;
	GameObject* player;

	AnimationRenderer* animRenderer;

	virtual void Update();
private:
	class GameScene& GetGameScene();
	void Move();
};
