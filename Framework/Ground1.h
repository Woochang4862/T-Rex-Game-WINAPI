#pragma once
#include "GameObject.h"
class Ground1 :
	public GameObject
{
public:
	Ground1();
	virtual void Update();
private:
	class GameScene& GetGameScene();
};

