#ifndef __UISYSTEM__
#define __UISYSTEM__

#include"main.h"

class UIsystem {
public:
	bool Button(D3DXVECTOR2 pos,D3DXVECTOR2 size);	// �}�E�X�Əd�Ȃ��Ă�����true��Ԃ�

	bool FadeOutAllUI(unsigned char *changeNum);				// �S�̂�UI�������������Ba�ɑ������ϐ���p�ӂ���B�����I�������true��Ԃ�
	void StartFadeOut();							// FadeOutAllUI���N������
	bool FadeInAllUI(unsigned char *changeNum);				// �S�̂�UI���������\���Ba�ɑ������ϐ���p�ӂ���B�\�����I�������true��Ԃ�
	void StartFadeIn();							// FadeInAllUI���N������


private:
	bool isFadeOut;
	bool isFadeIn;

};


#endif // !__UISYSTEM__
