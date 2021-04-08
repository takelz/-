#ifndef __SCENECLEAR__
#define __SCENECLEAR__


#include"SceneBase.h"
#include"BackGround.h"
#include"Dxg2d\Font.h"
#include"RankSystem.h"
#include"UIsystem.h"

class SceneClear :public SceneBase {
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

private:
	Font font;
	BackGround bg;
	RankSystem rankSystem;
	Sprite spriteButton;
	UIsystem uiSystem;

	bool orvered;
	unsigned char allAlpha;
};


#endif // !__SCENETITLE__
