//
// 余裕があったらRush系の仕様をPlayerクラスから切り離す
// 

#ifndef __PLAYER__
#define __PLAYER__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"PlayerManager.h"
#include"Move.h"
#include"HookShot.h"
#include"ObjEditMode.h"
#include"PlayerSensorCollider.h"

enum PlayerSprite {
	PLAYER_SPRITE_IDOL,
	PLAYER_SPRITE_MOVE,
	PLAYER_SPRITE_ATK,
	PLAYER_SPRITE_MAX,
};

//typedef struct {
//	int HP;
//
//}STATES;

class StopTimeGage :public GameObj{
public:
	void Init();
	void Update();
	void Draw();

	int currentGage;
	int maxGage;
private:

};


class Player:public GameObj{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	Player();

	//＝＝＝＝＝変数＝＝＝＝＝
	


private:

	void MovePos();


	void RushAttack();
	void Rush(D3DXVECTOR2 normDir);	
	void NextRush(D3DXVECTOR2 direction);
	void EndRush();
	
	void Damaged();
	
	void SelectSprite();
	void FollowCamera();					// カメラの追尾
	//＝＝＝＝＝変数＝＝＝＝＝
	
	Move move;
	HookShot hookShot;
	ObjEditMode edit;
	GroundedCollider groundedColl;	// 地面の設置判定
	StopTimeGage stopGage;

	// アニメーションスプライト
	Sprite *pCurSprite;		// 現在使っているスプライト
	Sprite moveSprite;
	Sprite atkSprite;
	Sprite atkEfectSprite;


	PlayerState state;	

	int rushTimeCnt;		// 突進のカウント
	int stopCnt;			// ストップ
	int invisibleCnt;		// 無敵時間
	int notStopTime;		// 攻撃開始後一定時間ストップしない変数
	float curDirect;		// 現在どちらを向いているか。1.0fで右
	PlayerSprite spriteNum;	// 
	bool loadedStart;		// スタート地点の座標を読み込んだか
	
	bool isJumped;		
	bool isDamaged;		

	//ステータス
	int HP;

};



#endif