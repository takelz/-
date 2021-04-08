#ifndef __UILIFE__
#define __UILIFE__

#include"main.h"
#include"Dxg2d\GameObj.h"
#include"Move.h"

class UILife: public GameObj {
public:
    void Init();
	void Update();
	void Draw();

private:
	int playerHP;
	Move move;
	float moveNum;
	float colorNum;
	unsigned char rgb;		// rgbÇ‹Ç∆ÇﬂÇƒïœçXÇ∑ÇÈÇΩÇﬂÇ…

};


#endif // !__UILIFE__
