#ifndef __UICOMBO__
#define __UICOMBO__

#include"main.h"
#include"Dxg2d\GameObj.h"
#include"Dxg2d\Font.h"

class UICombo{
public:
	void Init();
	void Update();
	void Draw();
private:

	int chain;
	Font font;
	Sprite spriteBack;
};


#endif // !__UISCORE__
