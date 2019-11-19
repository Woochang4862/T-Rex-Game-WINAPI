#pragma once
#include "GameObject.h"
#include "AnimationRenderer.h"
class Number :
	public GameObject
{
public:
	Number();
	AnimationRenderer* animRenderer;
	void SetNumber(int n);
};

