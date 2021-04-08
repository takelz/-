//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
// 2018/09/04	���c����	
// ���ʒ��߂��ł���悤�Ɏd�l�ύX
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "../main.h"
#include<xaudio2.h>

//*****************************************************************************
// �T�E���h�t�@�C��
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
	SOUND_LABEL_MAX,			// �o�^���̎����ݒ�
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);

void StopSound(SOUND_LABEL label);
void StopSound(void);

// �e���̒��߁A0.0f~1.0f(0~100%)
void SetVolume(SOUND_LABEL label, float volume);

#endif
