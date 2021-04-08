#ifndef __BLOCKROTATE__
#define __BLOCKROTATE__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"Ground.h"

class BlockRotate:public GameObj{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	void Create(float posX, float posY, float rotate, int numU, int numV,int num);

	//•Ï”

	bool exist;
private:
	ObjEditMode edit;
	void SwitchObj();
	int objNum;
};

#endif