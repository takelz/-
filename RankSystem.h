#ifndef __RANKSYSTEM__
#define __RANKSYSTEM__


#include"Dxg2d\GameObj.h"
#include"main.h"
#include"Dxg2d\Font.h"

enum {
	RANK_S,
	RANK_A,
	RANK_B,
	RANK_C,
	RANK_D,
	RANK_MAX,
};


class RANK {
public:
	int rank_S;
	int rank_A;
	int rank_B;
	int rank_C;

	RANK(int s, int a, int b, int c) {	// �A���t�@�l�ȊO���ꊇ�ŕς���
		rank_S = s;
		rank_A = a;
		rank_B = b;
		rank_C = c;
	}
	RANK() {};
private:

};

class RankSystem {
public:
	void Init();
	void Update();
	void Draw();

	unsigned char allAlpha;	// �t�F�[�h�p
	bool pushed;			// Continue����������

private:

	void Result();
	void PopRank();		
	void DispScore();

	RANK rank;
	Font font;
	Sprite spriteBack;	// �����N�����̔w�i

	Sprite spriteRank[RANK_MAX];// 4�̃����N�摜

	int resultRank;
	int resultScore;
	int stopCounter;	// �V�[���ؑ֒���ɏ����~�߂Ă�����s
	int rankPosY;		// ������o�Ă���p
	int rankAlpha;		// �����炾�񂾂�o�Ă���p

	bool endUp;			// �X�R�A�̃J�E���g���I�������
	bool playedSe;		// �����N�\���̌��ʉ���炵����

	bool rock;			// �ŏ������������~�߂�p
};

#endif // !__RANKSYSTEM__
