
#ifndef __MOVE__
#define __MOVE__

#include"main.h"

class Move {
public:

	// �w�肵�����W�ƖڕW�̍��W�Ƌ�����n���ċ��������߂�B�w�肵�ċ����ȓ��Ȃ�true��Ԃ�
	bool SearchTarget(D3DXVECTOR2 basePos,D3DXVECTOR2 targetPos,float distanceX,float distanceY);

	// �ڕW�̍��W���w�肵�����W�̉E���̏ꍇtrue��Ԃ�
	bool SearchDirectTargetX(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos);

	// �ڕW�̍��W���w�肵�����W�̉����̏ꍇtrue��Ԃ�
	bool SearchDirectTargetY(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos);

	// ��_�Ԃ�xy���W�̋��������߁A�w�苗�����Ȃ�true��Ԃ�
	bool DistancePosition(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos,float distance);

	// basePos����݂�targetPos���ǂ̕����ɂ��邩�𐳋K�����ꂽ�x�N�g���ŕԂ�
	D3DXVECTOR2 VectorDirection(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos);

	// �l��sign�g���g���ĕς��Ă���
	bool SignLoop(float *num,int speed,float range);

	// singloop�ƈꏏ�A���ގg�������ꍇ
	bool SignLoopB(float *num, int speed, float range);

	// �x�N�g������p�x�����߂�
	float AngleVector(D3DXVECTOR2 vec);

	// �F�̓_��(�������)
	void ColorBright(unsigned char *color, float *num, const int speed, const float range);


private:
	int signAngle;
	int signAngleB;
};




#endif // !__MOVE__
