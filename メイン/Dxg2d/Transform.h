// ���W�֌W
// 
//
// �`�X�V�����`
// 2018/07/24	�쐬
//

#ifndef __TRANSFORM__
#define __TRANSFORM__

//#include"../main.h"
#include"Sprite.h"
#include"StParam.h"


class Scale {
public:
	float x;
	float y;
};


class Transform {
public:
	//�����������֐�����������

	// transform�̏����X�v���C�g�ɍX�V
	void TransformToSprite(Sprite *sprite);	
	void SetTag(LPCSTR name);




	//�����������ϐ�����������
	D3DXVECTOR2 size;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scale;
	float rotate;
	bool notScroll;		// �X�N���[�������Ȃ�

	Transform();
	

private:
	D3DXVECTOR2 parentSize;
	D3DXVECTOR2 parentPos;
	float parentRotate;

};



#endif // !__TRANSFORM__
