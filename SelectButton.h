#ifndef __SELECTBUTTON__
#define __SELECTBUTTON__

#include"main.h"
#include"UIsystem.h"
#include"Dxg2d\Sprite.h"
#include"StageGenerate.h"

class SelectButton {
public:
	void Init(float posX,float posY,int number);
	void Update();
	void Draw();

	unsigned char alpha;		// SelectSystem����󂯎��p
private:
	bool overed;				// �T�E���h�p
	Sprite sprite;
	int stageNumber;		// �ǂ̃X�e�[�W�ւ̃{�^����
	UIsystem uiSystem;
	bool pushed;
};

#endif // !__SELECTBUTTON__
