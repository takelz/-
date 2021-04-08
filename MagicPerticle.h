#ifndef __MAGICPERTICE__
#define __MAGICPERTICE__

#include"main.h"
#include"Dxg2d/GameObj.h"

class MagicPerticle:public GameObj{
public:
	MagicPerticle();
	void Emit(D3DXVECTOR2 paramTrans, D3DXVECTOR2 paramVelocity);
	void Moving();
	void AdjustAlpha();
	void MoveCharge();
	void RandomColor();

	void Init();
	void Update();
	void Draw();
	void Uninit();

	//•Ï”
	float accPower;
	int endCnt;
	int moveCnt;
	bool exist;
};

#endif