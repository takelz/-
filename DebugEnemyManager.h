#ifndef __DEBUGENEMYMANAGER__
#define __DEBUGENEMYMANAGER__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"DebugEnemy.h"

#define MAX_ENEMY (16)

class DebugEnemyManager:public BaseManager{
public:

	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	void Create(float posX, float posY,float rotate,int num);

private:
	DebugEnemy enemy[MAX_ENEMY];
};

#endif