#ifndef __BLOCKROTATEMANAGER__
#define __BLOCKROTATEMANAGER__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"BlockRotate.h"
#include"GroundManager.h"

#define MAX_GROUND (64)

class BlockRotateManager{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	void Create(float posX, float posY,  float rotat,int num);

private:
	BlockRotate block[MAX_GROUND];
};

#endif