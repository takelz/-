#ifndef __SCENETITLE__
#define __SCENETITLE__


#include"SceneBase.h"
#include"BackGround.h"
#include"Dxg2d\Font.h"
#include"UIsystem.h"
#include"MagicEmitter.h"


class TitleSystem {
public:
	void Init();
	void Update();
	void Draw();

private:
	unsigned char allAlpha;
	bool overed;			// É}ÉEÉXÇ™êGÇÍÇΩÇ©
	Font font;
	Sprite titleName;
	Sprite startButton;
	UIsystem uiSystem;
};


class SceneTitle:public SceneBase {
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

private:


	BackGround bg;
	TitleSystem titleSystem;


};



#endif // !__SCENETITLE__
