
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

	bool enterOfDirX;	// �E���獶�ւ̐N�����B�x�N�g���Ŕ��f
	bool enterOfDirY;	// �E���獶�ւ̐N�����B�x�N�g���Ŕ��f
	bool enterPosDirX;	// �N�����I�u�W�F�N�g�̂ǂ��瑤�ɂ��邩
	bool enterPosDirY;	// �N�����I�u�W�F�N�g�̂ǂ��瑤�ɂ��邩

	bool rockTrriger;
};


#endif // !__HOOKSHOT__
