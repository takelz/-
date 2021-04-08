// ���Z����
// �I�u�W�F�N�g�̉����߂���
//
// �`�X�V�����`
// 2018/07/24	����
//
// ������������
// �n�`������Ƃ�isGround�̎g������
// �Ⴆ�Ώ�邱�Ƃ��o����G�Ȃ�Atrigger��on�̓G�{�̂Ƃ���ɏd�˂�n�`�p�̃I�u�W�F�N�g����肻���isGround��true�ɁB
// rigid.OnCollide()�͎g��Ȃ�
//
//
#ifndef __RIGIDBODY__
#define __RIGIDBODY__

#include"Transform.h"


class Rigidbody {
public:
	//�����������֐�����������

	void UpdatePos();	// ���W�̍X�V
	void OnCollide(float depth);	// ���̂ɏՓ˂����ۂɖ߂���
	void OnCollideSquareCircle(D3DXVECTOR2 target ,D3DXVECTOR2 lineAB, float lengthAB, D3DXVECTOR2 circlePos,float circleRadius);
	bool OnCollidePointCircle(D3DXVECTOR2 vecPtCircle, D3DXVECTOR2 target, float radius,D3DXVECTOR2 vecAB, float vecAB_Len);
	void OnCollideCircle(D3DXVECTOR2 baseCircle, float baseRadius, D3DXVECTOR2 targetCircle, float targetRadisus);
	void ResetVelocity();

	void Init(Transform *paramTransform);

	//�����������ϐ�����������
	D3DXVECTOR2 velocity;	//	���x
	D3DXVECTOR2 vector;		//	�ړ���
	D3DXVECTOR2 oldPos;		// 
	D3DXVECTOR2 oldVector;	// 1�t���[���O�̃x�N�g��
	bool useGravity;	// �d�͂�K�p�����邩
	bool useReflect;	// ���˂����邩(���x�͌������Ȃ�)

	bool reflected;		// ���˂������B�蓮�ł��ǂ�
	//float deceleration;	// �ǂ̂��炢�������邩(1.0f�Ō������Ȃ��B������傫�Ȓl���Ɖ�������)
	float mass;			// ����(���g�p)

private:
	//�����������֐�����������
	void RewindPos();							// �Փˎ��ɃI�u�W�F�N�g�������߂�
	void ReflectVector(D3DXVECTOR2 normalVec);	// ���˃x�N�g���B�^�C�~���O�͈ʒu������ɌĂяo��

	//�����������ϐ�����������
	Transform *pTransform;		// ������ɍs����(���g)�̏��
	Transform *pReceiveTrans;	// �󂯂鑤�̏��

	bool onCollide;				// �ǂɓ������Ă��Ƃɖ߂����ǂ���
	bool rockGravity;			// �n�ʂɓ������Ă��锻��Ȃ�d�̓��b�N
	bool isGround;				// �n�`������Ƃ邩	

};




#endif // !__RIGIDBODY__