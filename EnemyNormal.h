//移動のみの敵
//特殊な行動はしない
//
//
#ifndef __NORMALENEMY__
#define __NORMALENEMY__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"Ground.h"
#include"Move.h"

class EnemyNormalEffect :public GameObj{
public:
	void Init(float sizeX,float sizeY);
	void Update();
	void Draw();
private:
	Move move;
	float colorNum;	// 色変化用
};


class EnemyNormal : public GameObj{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	void Create(float posX, float posY, float rotat,int num);

	//＝＝＝＝＝変数＝＝＝＝＝

	bool exist;

protected:

	// プレイヤーに向かって進む
	void MoveToPlayer();

	// 左右か上下のsign波移動
	void MoveLoop(bool isSIde,float speed,float range);

	// 自身が進む方向を向く(スプライトを左右反転)
	void FaceToMove();

	// typeによる分岐
	void SelectMove();

	Move move;
	EnemyNormalEffect enemyEffect;
	ObjEditMode edit;
	//＝＝＝＝＝変数＝＝＝＝＝

	//振り分け
	int typeNum;	
};

#endif