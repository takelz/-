//移動のみの敵
//特殊な行動はしない
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

	bool isToge;;		// 現在攻撃状態か
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

	//＝＝＝＝＝変数＝＝＝＝＝

	bool exist;

private:

	void SetupToge();

	//＝＝＝＝＝変数＝＝＝＝＝

	//振り分け
	int typeNum;	
	ObjEditMode edit;
	Sprite spriteCloss;
	Sprite spriteEffect;

	TogeObj togeObj;
	
};





#endif