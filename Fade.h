
// StartFade����ꍇ���Ȃ炸GetState�̂����ɏ���������
//

#ifndef __FADE__
#define __FADE__

#include"Dxg2d\Sprite.h"
#include"main.h"
#include"Dxg2d\Font.h"

class Fade {
public:
	static Fade *Instance() {
		static Fade fade;
		return &fade;
	}
	static void Delete() {
		delete Instance();
	}

	void Init();
	void Update();
	void Draw();

	void StartFadeOut();// �t�F�[�h�A�E�g
	//bool EndFadeOut();	// �t�F�[�h�A�E�g���I�������true��Ԃ�
	void StartFadeIn();	// �t�F�[�h�C��
	//bool EndFadeIn();	// �t�F�[�h�C�����I�������true��Ԃ�

	bool GetFadeState(bool isOut);	// �Ăяo�����Ƃ�true�Ȃ�false�ɖ߂�
private:
	void FadeIn();
	void FadeOut();

	Sprite sprite;
	Font font;			// ���[�h�\��
	bool dispLoading;	// �t�F�[�h�A�E�g�I������true�ŕ\��
	bool flagIn;
	bool flagOut;
	bool endFadeOut;	// true�ŏI�������
	bool endFadeIn;	// true�ŏI�������


	float accNum;	// �t�F�[�h�̉���
};

// ���ʂ̈Â��Ȃ�t�F�[�h
class NormalFade {
public:
	static NormalFade *Instance() {
		static NormalFade normalFade;
		return &normalFade;
	}
	static void Delete() {
		delete Instance();
	}

	void Init();
	void Update();
	void Draw();

	void StartFadeIn();
	void StartFadeOut();
	bool EndFadeIn();
	bool EndFadeOut();

	void SetGray(bool isGray);		// ���Â���Ԃɂ��邩

private:
	void FadeIn();
	void FadeOut();
	void ScreenGray();

	bool flagIn;
	bool flagOut;

	bool flagGray;	// ���Â����

	Sprite sprite;
};


#endif // !__FADE__
