#ifndef __UISCORE__
#define __UISCORE__

#include"main.h"
#include"Dxg2d\GameObj.h"
#include"Dxg2d\Font.h"

class UIScore :public GameObj {
public:
	void Init();
	void Update();
	void Draw();
private:
	void ScoreUp();
	void DispUp();	// �X�R�A�A�b�v�̕\��

	int score;
	int upNum;		// �ǂ̂��炢�X�R�A�A�b�v������
	int upNumAlpha;	// 
	int upNumPos;
	bool isUpEnd;	// �X�R�A�A�b�v���ʒu�ɂ���������Ă���

	bool upRock;	// �d�l��v���C���[�̃A�^�b�N��false�ɂȂ�܂ŘA���ŃX�R�A�A�b�v���Ȃ��悤��
	Font font;
	Sprite spriteBack;
};


#endif // !__UISCORE__
