// �R���C�_�̓o�^���
//
// �`�X�V�����`
// 2018/07/24	����
//


#ifndef __COLLISION_STATE__
#define __COLLISION_STATE__

//#include"StParam.h"
#include"Transform.h"

#define MAX_NOTCOLL_NUM (16)


enum CollisionType {
	C_TYPE_SQUARE,
	C_TYPE_CIRCLE,
};

// �v�Z�p�̍\����
typedef struct {
	float leftX;	// ��X
	float rightX;	// �EX
	float upY;		// ��Y
	float downY;	// ��Y
	float centerX;	// ���SX
	float centerY;	// ���SY
	float radiusX;	// ���aX(���S����̋���)
	float radiusY;	// ���aY
	float rotate;
}CollCalcNum;

// ���_
typedef struct {
	float x;
	float y;
}LINEPOINT;

// �R���C�_���ߗp�̍\����
typedef struct {
	float top;		// �㕔
	float bottom;	// ����
	float left;		// ��
	float right;	// �E
	float radius;	// ���a(�R���C�_���~�̏ꍇ)
	D3DXVECTOR2 pos;// �ʒu
}EDITCOLLIDER;


// �R���C�_�̕ۑ�
class CollisionState {
public:

	//�����������֐�����������

	CollisionState();
	CollisionState(Transform *paramTransform, TagName paramTagName, int registerNum,CollisionType paramType, TagName *notCollArray,EDITCOLLIDER *editColl);
	CollCalcNum CollisionState::CalcPosNum();

	//�����������ϐ�����������

	Transform		*pTransform;	// ���W�̃A�h���X��ۑ�
	TagName			tagName;		// �����p�̃^�O��
	CollisionType	type;			// �R���C�_�̃^�C�v(��)
	TagName			*notCollideTag;
	EDITCOLLIDER	*editCollider;

	unsigned int collNum;	// �R���C�_�̌ʔԍ�
	bool	enable;			// �R���C�_���L����
	bool	trigger;		// true�Ȃ畨�̂͊ђʂ���

private:
	CollCalcNum cPos;
};




#endif // !__COLLISION_STATE__
