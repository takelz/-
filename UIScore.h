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
	void DispUp();	// スコアアップの表示

	int score;
	int upNum;		// どのぐらいスコアアップしたか
	int upNumAlpha;	// 
	int upNumPos;
	bool isUpEnd;	// スコアアップが位置についたら消えていく

	bool upRock;	// 仕様上プレイヤーのアタックがfalseになるまで連続でスコアアップしないように
	Font font;
	Sprite spriteBack;
};


#endif // !__UISCORE__
