//ˆÚ“®‚Ì‚İ‚Ì“G
//“Áê‚Ès“®‚Í‚µ‚È‚¢
//
//
#ifndef __ENEMYSHIELD__
#define __ENEMYSHIELD__

#include"main.h"
#include"EnemyNormal.h"
#include"Dxg2d/GameObj.h"
#include"Ground.h"
#include"Move.h"

#define ENEMY_SHIELD_NUM (2)


class ShieldObj :public GameObj {
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
private:
	

};


class EnemyShield : public EnemyNormal{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();

	void Create(float posX, float posY, float rotat,int num);

	//•Ï”

	bool exist;

private:

	void SetupShield();

	//•Ï”

	//U‚è•ª‚¯
	int typeNum;	
	ObjEditMode edit;

	ShieldObj shieldObj[ENEMY_SHIELD_NUM];
	
};





#endif