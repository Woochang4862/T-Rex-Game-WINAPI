#include "stdafx.h"
#include "Number.h"
#include "AnimationRenderer.h"
#include "ListAnimation.h"

Number::Number()
	:GameObject(animRenderer = new AnimationRenderer())
{
	ListAnimation* n1 = new ListAnimation(1, 1.0f);
	n1->PushBackSprite(L"resources/number/1.png");
	ListAnimation* n2 = new ListAnimation(2, 1.0f);
	n2->PushBackSprite(L"resources/number/2.png");
	ListAnimation* n3 = new ListAnimation(3, 1.0f);
	n3->PushBackSprite(L"resources/number/3.png");
	ListAnimation* n4 = new ListAnimation(4, 1.0f);
	n4->PushBackSprite(L"resources/number/4.png");
	ListAnimation* n5 = new ListAnimation(5, 1.0f);
	n5->PushBackSprite(L"resources/number/5.png");
	ListAnimation* n6 = new ListAnimation(6, 1.0f);
	n6->PushBackSprite(L"resources/number/6.png");
	ListAnimation* n7 = new ListAnimation(7, 1.0f);
	n7->PushBackSprite(L"resources/number/7.png");
	ListAnimation* n8 = new ListAnimation(8, 1.0f);
	n8->PushBackSprite(L"resources/number/8.png");
	ListAnimation* n9 = new ListAnimation(9, 1.0f);
	n9->PushBackSprite(L"resources/number/9.png");
	ListAnimation* n0 = new ListAnimation(0, 1.0f);
	n0->PushBackSprite(L"resources/number/0.png");
	animRenderer->PushBackAnimation(n1);
	animRenderer->PushBackAnimation(n2);
	animRenderer->PushBackAnimation(n3);
	animRenderer->PushBackAnimation(n4);
	animRenderer->PushBackAnimation(n5);
	animRenderer->PushBackAnimation(n6);
	animRenderer->PushBackAnimation(n7);
	animRenderer->PushBackAnimation(n8);
	animRenderer->PushBackAnimation(n9);
	animRenderer->PushBackAnimation(n0);
}

void Number::SetNumber(int n)
{
	animRenderer->ChangeAnimation(n);
}


