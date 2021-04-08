//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
// 2018/09/04	武田正光	
// 音量調節ができるように仕様変更
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "../main.h"
#include<xaudio2.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_BGM_GAME,
	SOUND_BGM_MENU,
	SOUND_ENTER,
	SOUND_MOUSEOVER,
	SOUND_FADEIN,
	SOUND_FADEOUT,
	SOUND_COUNTUP,
	SOUND_ATTACKSTART,
	SOUND_DAMAGE,
	SOUND_DESTORY,
	SOUND_LABEL_MAX,			// 登録数の自動設定
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);

void StopSound(SOUND_LABEL label);
void StopSound(void);

// 各音の調節、0.0f~1.0f(0~100%)
void SetVolume(SOUND_LABEL label, float volume);

#endif
