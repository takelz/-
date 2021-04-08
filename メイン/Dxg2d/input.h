// DirectInput
// メモ：トリガとリリース
// DirectInputが返す情報は「現在そのキーが押されているか否か」だけである。
// 毎回直前の値をアプリが覚えるのは面倒なため、入力ライブラリなどであらかじめトリガの値を計算し参照できるようにする。
#ifndef _INPUT_H_
#define _INPUT_H_

#define DIRECTINPUT_VERSION	0x0800	// DirectX8 を明示
#include <dinput.h>					// DirectInput 関連のヘッダ

#include "../main.h"

#define DIK_LEFT_CLICK (0)
#define DIK_RIGHT_CLICK (1)

// プロトタイプ宣言
HRESULT InitDInput(HWND hWnd);
void UninitDInput();
void UpdateDInput();

bool DIGetKey(DWORD dwKey);
bool DIGetKeyTrigger(DWORD dwKey);
bool DIGetKeyRelease(DWORD dwKey);
DWORD DIGetJoyCount();
DIJOYSTATE *DIGetJoy(DWORD dwJoy);
LONG DIGetJoyX(DWORD dwJoy);
LONG DIGetJoyY(DWORD dwJoy);
LONG DIGetJoyZ(DWORD dwJoy);
bool DIGetJoyButton(DWORD dwJoy, DWORD dwBtn);
bool DIGetJoyTrigger(DWORD dwJoy, DWORD dwBtn);
bool DIGetJoyRelease(DWORD dwJoy, DWORD dwBtn);
DIMOUSESTATE *DIGetMouse();
bool DIGetMouseButton(DWORD dwBtn);
bool DIGetMouseTrigger(DWORD dwBtn);
bool DIGetMouseRelease(DWORD dwBtn);

#endif
