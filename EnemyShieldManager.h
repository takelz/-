#ifndef __ENEMYSHIELDMANAGER__
#define __ENEMYSHIELDMANAGER__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"EnemyShield.h"

#define MAX_ENEMY (16)

class EnemyShieldManager:public BaseManager{
public:

	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	void Create(float posX, float posY,float rotate,int num);

private:
	EnemyShield enemy[MAX_ENEMY];
};

#endif