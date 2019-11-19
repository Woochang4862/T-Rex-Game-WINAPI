#include "stdafx.h"
#include "ReplayIcon.h"

ReplayIcon::ReplayIcon()
	:GameObject(L"resources/replay-image.png")
{
	transform->SetPosition(600.0f, 373.5f);
	transform->SetScale(0.0f, 0.0f);
}
