#ifndef __GROUNDMANAGER__
#define __GROUNDMANAGER__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"Ground.h"

#define MAX_NORMALGROUND (128)

class GroundManager{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	
	void Create(float posX, float posY,float rotat,int num);
	~GroundManager() {};
private:
	Ground ground[MAX_NORMALGROUND];
};

#endif