// �v���C���[�̒n�ʐڒn���蓙
//
#ifndef __PLAYERSENSORCOLLIDER__
#define __PLAYERSENSORCOLLIDER__

#include"main.h"
#include"Dxg2d\GameObj.h"


class GroundedCollider:public GameObj {
public:
	void Init();
	void Update();
	void Draw();		// �f�o�b�N�p
	
	bool isJumped;		// �W�����v���������(�n�ʂɒ����܂ŉ񕜂��Ȃ�)


private:
	bool isGround;		// ���n�ʂɑ������Ă��邩


};


#endif // !__PLAYERSENSORCOLLIDER__