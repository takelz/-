#ifndef __SELECTSYSTEM__
#define __SELECTSYSTEM__

#include"main.h"
#include"SelectButton.h"
#include"Dxg2d\Font.h"

#define  MAX_SELECT_BUTTON (5)	// �K������

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
	unsigned char allAplha;		// �V�[���J�ڗp
};

#endif // !__SELECTSYSTEM__
