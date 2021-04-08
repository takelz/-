#ifndef __ENEMYTOGEMANAGER__
#define __ENEMYTOGEMANAGER__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"EnemyToge.h"

#define MAX_ENEMY (16)

class EnemyTogeManager:public BaseManager{
public:

	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	void Create(float posX, float posY,float rotate,int num);

private:
	EnemyToge enemy[MAX_ENEMY];
};

#endif