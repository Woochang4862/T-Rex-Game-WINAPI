#include "stdafx.h"
#include "GameOverText.h"

GameOverText::GameOverText()
	:GameObject(L"resources/game-over-text.png")
{
	transform->SetPosition(600.0f,300.0f);
	transform->SetScale(0.0f, 0.0f);
}
