// DirectInput
// �����F�g���K�ƃ����[�X
// DirectInput���Ԃ����́u���݂��̃L�[��������Ă��邩�ۂ��v�����ł���B
// ���񒼑O�̒l���A�v�����o����͖̂ʓ|�Ȃ��߁A���̓��C�u�����Ȃǂł��炩���߃g���K�̒l���v�Z���Q�Ƃł���悤�ɂ���B
#ifndef _INPUT_H_
#define _INPUT_H_

#define DIRECTINPUT_VERSION	0x0800	// DirectX8 �𖾎�
#include <dinput.h>					// DirectInput �֘A�̃w�b�_

#include "../main.h"

#define DIK_LEFT_CLICK (0)
#define DIK_RIGHT_CLICK (1)

// �v���g�^�C�v�錾
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
