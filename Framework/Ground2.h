#pragma once
#include "GameObject.h"
class Ground2 :
	public GameObject
{
public:
	Ground2();
	virtual void Update();
private:
	class GameScene& GetGameScene();
};

