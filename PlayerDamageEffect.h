#ifndef __PLAYERDAMAGEEFECT__
#define __PLAYERDAMAGEEFECT__

#include"main.h"
#include"Dxg2d/GameObj.h"

class ScreenEffect:public GameObj {
public:
	void Init();
	void Update();
	void Draw();
};

class PlayerDamageEffect:public GameObj{
public:
	void Init();
	void Update();
	void Draw();
private:
	Sprite effect;
	ScreenEffect screenEffect;
};

#endif