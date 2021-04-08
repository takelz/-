#ifndef __SCENEOVER__
#define __SCENEOVER__


#include"SceneBase.h"
#include"BackGround.h"
#include"Dxg2d\Font.h"
#include"PlayerDamageEffect.h"
#include"UIsystem.h"
#include"Move.h"

class SceneOver :public SceneBase {
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

private:
	bool overed;			// É}ÉEÉXÇ™êGÇÍÇΩÇ©
	bool pushed;
	unsigned char color;
	float colorNum;

	Move move;
	Font font;
	BackGround bg;
	PlayerDamageEffect damageffect;
	Sprite spriteButton;
	UIsystem uiSystem;
};


#endif // !__SCENETITLE__
