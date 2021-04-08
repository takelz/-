//
//シングルトン
//

#ifndef __PLAYERMANAGER__
#define __PLAYERMANAGER__

#include"main.h"
#include"Dxg2d/GameObj.h"


enum  PlayerState {
	PLAYER_NORMAL,		
	PLAYER_ATACK,		// 空中突進状態
	PLAYER_DAMAGED,		// 被ダメージ中
	PLAYER_STATE_MAX,
};



class PlayerManager{
public:
	static PlayerManager *Instance() {
		static PlayerManager playerManager;
		return &playerManager;
	}
	static void Delete() {
		delete Instance();
	}



	// プレイヤーへ与える攻撃情報
	void SetAtackedEnemy(D3DXVECTOR2 paramKnockBack);
	// プレイヤーへ与える攻撃情報
	void SetAtackedEnemy();

	// プレイヤーがもらう攻撃情報。攻撃が当たったらtrueを返す
	bool GetAttackedState(D3DXVECTOR2 *paramKnockBack);

	// プレイヤーがもらう攻撃情報。攻撃が当たったらtrueを返す
	bool GetAttackedState();

	// 突撃回数の取得。0は突撃してない
	int GetRushCount();

	// 突撃回数を増やす
	void CountUpRush();
	// 突撃回数リセット。0に
	void ResetRushCount();

	// フックショットの開始
	void StartHook(D3DXVECTOR2 posision);

	// 敵が無事プレイヤーの突撃攻撃を受けたら
	void SendRushSuccess();

	// プレイヤーが取得するスタートポジション
	D3DXVECTOR2 GetStartPos();


	//＝＝＝＝＝変数＝＝＝＝＝

	PlayerState state;
	D3DXVECTOR2 pos;	
	bool attackSuccess;		// 突進攻撃が成功したか
	D3DXVECTOR2 hookPoint;
	D3DXVECTOR2 startPos;	// スタート
	bool hookOn;
	bool enemyAtacked;		// 敵が攻撃したかどうか。プレイヤーはこれに直接アクセスしないこと
	int playerHP;

private:

	PlayerManager() {};
	~PlayerManager() {};



	D3DXVECTOR2 knockBack;	// ノックバックのベクトル
	int rushCount;			// 現在の突撃回数

};

#endif