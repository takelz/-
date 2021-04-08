//�V���O���g��
//
//�J�����̏���
//�I�u�W�F�N�g�̍��W�̓J�������W����̑��΋���
//
//�`�X�V�����`
//2018/07/24	����
//

#ifndef __CAMERA__
#define __CAMERA__

#include"../main.h"
//#include"StParam.h"



class Camera {
public:
	static Camera *Instance() {
		static Camera camera;
		return &camera;
	}
	static void Delete() {
		delete Instance();
	}

	void ShakeUpdate();	// �J�����U���A��ɃA�b�v�f�[�g��
	void Shake();		// �J�����U���̓ǂݏo��

	//�����������ϐ�����������
	D3DXVECTOR2 shakeOffset;	// �U���ɂ����W�Y��
	D3DXVECTOR2 pos;
	
private:
	float shakeNum;
	float shakeRange;

	float signAngle;
	bool direction;		// �U���̌���

	Camera() {};
	~Camera() {};
};


#endif // !__TRANSFORM__
