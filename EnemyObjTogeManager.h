#ifndef __ENEMYOBJTOGEMANAGER__
#define __ENEMYOBJTOGEMANAGER__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"EnemyObjToge.h"

#define MAX_TOGEENEMY (32)

class EnemyObjTogeManager :public BaseManager {
public:

	void Init();
	void Update();
	void Draw();
	void EditUpdate();

	void Create(float posX, float posY, float rotate, int num);

private:
	EnemyObjToge enemy[MAX_TOGEENEMY];
};

#endif