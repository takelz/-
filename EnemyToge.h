//ˆÚ“®‚Ì‚İ‚Ì“G
//“Áê‚Ès“®‚Í‚µ‚È‚¢
//
//
#ifndef __ENEMYTOGE__
#define __ENEMYTOGE__
  
#include"main.h"
#include"EnemyNormal.h"
#include"Dxg2d/GameObj.h"
#include"Ground.h"
#include"Move.h"

class TogeObj :public GameObj {
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

	bool isToge;;		// Œ»İUŒ‚ó‘Ô‚©
private:

	Move move;

};


class EnemyToge : public EnemyNormal{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();

	void Create(float posX, float posY, float rotat,int num);

	//•Ï”

	bool exist;

private:

	void SetupToge();

	//•Ï”

	//U‚è•ª‚¯
	int typeNum;	
	ObjEditMode edit;
	Sprite spriteCloss;
	Sprite spriteEffect;

	TogeObj togeObj;
	
};





#endif