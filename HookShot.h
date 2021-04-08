
#ifndef __HOOKSHOT__
#define __HOOKSHOT__

#include"main.h"
#include"Move.h"
#include"Dxg2d\Transform.h"


class HookShot {
public:
	void Hook(D3DXVECTOR2 basePos,D3DXVECTOR2 *baseVector);
	void CheckDirection(D3DXVECTOR2 basePos, D3DXVECTOR2 baseVector);

private:
	const bool RIGHT = 1;
	const bool LEFT = 0;
	const bool DOWN = 1;
	const bool UP = 0;

	Move move;

	bool enterOfDirX;	// 右から左への侵入か。ベクトルで判断
	bool enterOfDirY;	// 右から左への侵入か。ベクトルで判断
	bool enterPosDirX;	// 侵入時オブジェクトのどちら側にいるか
	bool enterPosDirY;	// 侵入時オブジェクトのどちら側にいるか

	bool rockTrriger;
};


#endif // !__HOOKSHOT__
