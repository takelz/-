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

	RANK(int s, int a, int b, int c) {	// アルファ値以外を一括で変える
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

	unsigned char allAlpha;	// フェード用
	bool pushed;			// Continueをおしたか

private:

	void Result();
	void PopRank();		
	void DispScore();

	RANK rank;
	Font font;
	Sprite spriteBack;	// ランク文字の背景

	Sprite spriteRank[RANK_MAX];// 4つのランク画像

	int resultRank;
	int resultScore;
	int stopCounter;	// シーン切替直後に少し止めてから実行
	int rankPosY;		// 下から出てくる用
	int rankAlpha;		// 下からだんだん出てくる用

	bool endUp;			// スコアのカウントが終わったら
	bool playedSe;		// ランク表示の効果音を鳴らしたか

	bool rock;			// 最初少し動きを止める用
};

#endif // !__RANKSYSTEM__
