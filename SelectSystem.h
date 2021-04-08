#ifndef __SELECTSYSTEM__
#define __SELECTSYSTEM__

#include"main.h"
#include"SelectButton.h"
#include"Dxg2d\Font.h"

#define  MAX_SELECT_BUTTON (5)	// 必ず偶数

class SelectSystem {
public:
	void Init();
	void Update();
	void Draw();

private:

	void PutButton();

	Font font;
	SelectButton selectButton[MAX_SELECT_BUTTON];
	Sprite returnButton;

	bool pushed;
	UIsystem uiSystem;
	unsigned char allAplha;		// シーン遷移用
};

#endif // !__SELECTSYSTEM__
