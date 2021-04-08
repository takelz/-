// �R���C�_�֘A
// �R���C�_�̒���Rigidbody���܂�
// �n�`����ɂ������I�u�W�F�N�g��Oncollide�����Ȃ�
//
// �`�X�V�����`
// 2018/07/24	����
// 2018/07/25	�֐����ύX
//

#ifndef __COLLISION__
#define __COLLISION__



#include"Transform.h"
#include"CollisionState.h"
#include"Rigidbody.h"
 

// �o�^���Ă���R���C�_���擾���邽�߂̍\����
typedef struct {
	CollCalcNum num;
	CollisionType type;
	bool trigger;
	TagName notCollideTag[MAX_NOTCOLL_NUM];
	TagName tag;
}COLL_CALC_ST;


class Collision {
public:
	//�����������֐�����������

	// �R���C�_�̓o�^�B�R���C�_�g���Ȃ�K���R���X�g���N�^�ŌĂяo��
	void Register(Transform *transform, TagName paramTagName,CollisionType collType);

	// �R���C�_�̍폜�B�����Ƃ��ɕK���Ăяo��
	void DeleteCollision();
	
	// �^�O�̕ύX
	void SetTag(TagName tagName);

	// �L����
	void SetEnable(bool enable);

	// �ђʂ��邩
	void SetTrigger(bool trigger);

	// �ђʂ���������̃^�O��o�^(16�܂�)
	void SetNotCollideTag(TagName tag);

	// �ђʂ���������̃^�O�̓o�^����
	void DeleteNotCollideTag(TagName tag);

	bool OnCollide(TagName targetTag);

	Collision();
	~Collision();

	//�����������ϐ�����������

	Rigidbody rigid;		// �����֌W
	bool trigger;
	EDITCOLLIDER editColl;	// �R���C�_�̈ʒu�傫���̒��߁B�~�̏ꍇ�͑傫���ύX��radius�����ł悢

private:
	COLL_CALC_ST* SeachState(TagName tagName);
	CollCalcNum GetCalcNum();	
	bool LineCollide(LINEPOINT pointA, LINEPOINT pointB, LINEPOINT targetA, LINEPOINT targetB);
	bool Square(COLL_CALC_ST *collCalc);
	bool Circle(COLL_CALC_ST *collCalc);
	bool SquareCircle(COLL_CALC_ST *pSquare,COLL_CALC_ST *pCircle);
	bool CheckNotCollideTag(TagName *baseTag, TagName targetTag);		

	int collRegisterNum;	// �R���C�_�̌ʔԍ�
	TagName tagName;		// ���̃I�u�W�F�N�g�̃^�O
	CollisionType type;
	Transform *pCollTrans;	// ���W����ۑ�	
	TagName notCollideTag[MAX_NOTCOLL_NUM];	// ��v�̃R���C�_�̃^�O�Ɣ��肵�Ȃ�����ۑ��B0�ŉ��������Ă��Ȃ�

};

void ResetCollisionDeque();	// �ۑ����Ă���R���C�_�����ׂď�����

#endif // !__COLLISION__

