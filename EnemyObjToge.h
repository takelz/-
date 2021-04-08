
#ifndef __ENEMYOBJTOGE__
#define __ENEMYOBJTOGE__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"ObjEditMode.h"
#include"Move.h"

class EnemyObjToge : public GameObj {
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	void Create(float posX, float posY, float rotate, int num);

	//•Ï”

	bool exist;
private:
	void Bright();

	float brightNum;	// “_–Å—p

	Move move;
	ObjEditMode edit;
	//U‚è•ª‚¯
	int typeNum;
};


#endif // !__NORMALENEMY__