#ifndef __DEBUGENEMY__
#define __DEBUGENEMY__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"Ground.h"
#include"Move.h"


class DebugEnemy : public GameObj{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	void Create(float posX, float posY, float rotat);

	//•Ï”

	bool exist;

private:
	ObjEditMode edit;
	Move move;
};

#endif