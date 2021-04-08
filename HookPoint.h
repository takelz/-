
#ifndef  __HOOKPOINT__
#define __HOOLPOINT__

#include"main.h"
#include"Dxg2d\GameObj.h"
#include"Move.h"


class HookPoint: GameObj{
public:
	void Hook(D3DXVECTOR2 position);

private:
	D3DXVECTOR2 thisPoint;
};



#endif // ! __HOOKPOINT__
