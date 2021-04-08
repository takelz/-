//�ړ��݂̂̓G
//����ȍs���͂��Ȃ�
//
//
#ifndef __ENEMYSHIELD__
#define __ENEMYSHIELD__

#include"main.h"
#include"EnemyNormal.h"
#include"Dxg2d/GameObj.h"
#include"Ground.h"
#include"Move.h"

#define ENEMY_SHIELD_NUM (2)


class ShieldObj :public GameObj {
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
private:
	

};


class EnemyShield : public EnemyNormal{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();

	void Create(float posX, float posY, float rotat,int num);

	//�����������ϐ�����������

	bool exist;

private:

	void SetupShield();

	//�����������ϐ�����������

	//�U�蕪��
	int typeNum;	
	ObjEditMode edit;

	ShieldObj shieldObj[ENEMY_SHIELD_NUM];
	
};





#endif