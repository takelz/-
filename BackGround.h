#ifndef __BACKGROUND__
#define __BACKGROUND__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"MagicEmitter.h"

class BackGround:public GameObj{
public:
	void Init();
	void Update();
	void Draw();

private:
	//MagicEmitter magicEmitter;
};

#endif