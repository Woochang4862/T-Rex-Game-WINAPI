#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
#include "Obstacle.h"
#include "Scene.h"
#include "AnimationRenderer.h"
#include "SoundEvent.h"

//Player�� ���Ƿ� ������ ��ü�Դϴ�.
//���� ���� ������Ʈ�� GameObject��ü�� ��ӹ޾� �����Ͽ����մϴ�.
class Player :
	public GameObject
{
public:
	bool isJumping;
	float jumpTime;
	float jumpAccell;
	float gravity;
	float jumpPower;
	float posY;

	AABBCollider col;		//�浹�� ������ ����
	Obstacle* enemy;		//���� �� �ٸ� ��ü

	AnimationRenderer* animRenderer;		//�ִϸ��̼Ƿ�����. �ִϸ��̼��� ������ �� �ʿ�

	SoundEvent* se;		//�����̺�Ʈ
	
	Player();					//Player������
	virtual void Update();		//Update: �� ������ ȣ��˴ϴ�.
	virtual void LateUpdate();	//LateUpdate: �� ������ Update, Render�� ����� ���� ȣ��˴ϴ�.
	void Jump();
private:
	class GameScene& GetGameScene();
};