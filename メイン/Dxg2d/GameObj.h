// �Q�[���I�u�W�F�N�g
// �Q�[���̊�{�I�ȗv�f�B
//
// �`�X�V�����`
//

#ifndef __GAMEOBJ__
#define __GAMEOBJ__

#include"Sprite.h"
#include"Transform.h"
#include"Collision.h"

class GameObj {
protected:
	Transform transform;
	Sprite sprite;
	Collision collision;



public:
	// �q�I�W�F�N�g�̍X�V�B
	void AttachChild(Transform *parentTransform, D3DXVECTOR2 offsetPos);
	// �q�I�W�F�N�g�̍X�V�B
	void AttachChild(Transform *parentTransform,float offsetX,float offsetY);
	// �q�I�W�F�N�g�̍X�V�B
	void AttachChild(Transform *parentTransform);

};



#endif // !
