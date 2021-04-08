//=============================================================================
//
// メイン処理 [main.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_ 
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
//#include"Dxg2d\Sprite.h"


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#if 1 // [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル "に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH (800+160)  	 	 	// ウインドウの幅
#define SCREEN_HEIGHT (600+120)  	 	 	// ウインドウの高さ
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2) // ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2) // ウインドウの中心Ｙ座標

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x) x->Release(); x = NULL;}
#endif // !

//＝＝＝＝＝ゲームオブジェクトのタグ設定＝＝＝＝＝
enum TagName {
	//TAG_NOT = 0,	// 使わない
	TAG_GROUND = 1,
	TAG_ENEMY,
	TAG_ENEMYB,
	TAG_PLAYER,
	TAG_GOAL,
	TAG_NOT,		// 未割当
	TAG_MAX,
};

// 付け加える時は下に追加していく。
enum Manager {
	MANAGER_PLAYER,
	MANAGER_GROUND,
	MANAGER_BLOCKROTATE,
	MANAGER_DEBUGENEMY,
	MANAGER_ENEMYNORMAL,
	MANAGER_ENEMYSHIELD,
	MANAGER_ENEMYTOGE,
	MANAGER_OBJTOGE,
	MANAGER_GOAL,			// これはマネージャーではない
	MANAGER_POP,
	MANAGER_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
HWND GetHwnd();						// ウィンドウ情報取得
D3DXVECTOR2 GetMousePos();			// 画面内のマウスの座標(カメラの座標は考慮していない)
void SetOnDestBlend();				// 加算合成をオン、使ったら最後にかならずオフにする
void SetOffDestBlend();				// 加算合成をオフ
void SetOnBlendOne();
void SetOffBlendOne();

bool IsOutScreen(D3DXVECTOR2 pos);	// 対象が画面範囲外にいるかどうか

// マネージャーの基底クラス
class BaseManager {

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void EditUpdate() = 0;	// ステージエディット用更新処理
	virtual void Draw() = 0;
	//virtual void Uninit() = 0;

	virtual void Create(float posX, float posY, float rotate, int num) = 0;

private:
protected:


};

#endif // _MAIN_H_
