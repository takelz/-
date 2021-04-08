#ifndef __ENEMYNORMALMANAGER__
#define __ENEMYNORMALMANAGER__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"EnemyNormal.h"

#define MAX_NORMALENEMY (32)

class EnemyNormalManager:public BaseManager{
public:

	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	
	void Create(float posX, float posY,float rotate,int num);

private:
	EnemyNormal enemy[MAX_NORMALENEMY];
};

#endif