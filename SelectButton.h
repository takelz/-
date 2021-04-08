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

	unsigned char alpha;		// SelectSystemから受け取る用
private:
	bool overed;				// サウンド用
	Sprite sprite;
	int stageNumber;		// どのステージへのボタンか
	UIsystem uiSystem;
	bool pushed;
};

#endif // !__SELECTBUTTON__
