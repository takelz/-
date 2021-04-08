// DirectInput
#include "input.h"

#pragma comment(lib, "dinput8")

//----- �}�N����`
#define MAX_JOY		8		// �ő�ڑ���
#define JOY_MIN_X	-32768	// �w���ŏ��l
#define JOY_MAX_X	32767	// �w���ő�l
#define JOY_MIN_Y	-32768	// �x���ŏ��l
#define JOY_MAX_Y	32767	// �x���ő�l

//----- �O���[�o���ϐ�
static LPDIRECTINPUT8		g_pDI;							// DirectInput8 �I�u�W�F�N�g
static LPDIRECTINPUTDEVICE8	g_pDIDeviceKey;					// �L�[�{�[�h �I�u�W�F�N�g
static LPDIRECTINPUTDEVICE8	g_pDIDeviceJoy[MAX_JOY];		// �Q�[���p�b�h �I�u�W�F�N�g
static LPDIRECTINPUTDEVICE8	g_pDIDeviceMouse;				// �}�E�X �I�u�W�F�N�g
static BYTE					g_bKeyState[256];				// �L�[�{�[�h���
static BYTE					g_bPrevKeyState[256];			// �O��̃L�[�{�[�h���
static BYTE					g_bKeyTriggerState[256];		// �L�[�{�[�h �g���K���
static BYTE					g_bKeyReleaseState[256];		// �L�[�{�[�h �����[�X���
static DIMOUSESTATE			g_diMouseState;					// �}�E�X���
static DIMOUSESTATE			g_diPrevMouseState;				// �O��̃}�E�X���
static DIMOUSESTATE			g_diMouseTriggerState;			// �}�E�X �g���K���
static DIMOUSESTATE			g_diMouseReleaseState;			// �}�E�X �����[�X���
static DWORD				g_dwJoystick;					// �Q�[���p�b�h�ڑ���
static DIJOYSTATE			g_diJoyState[MAX_JOY];			// �Q�[���p�b�h���
static DIJOYSTATE			g_diPrevJoyState[MAX_JOY];		// �O��̃Q�[���p�b�h���
static DIJOYSTATE			g_diJoyTriggerState[MAX_JOY];	// �Q�[���p�b�h �g���K���
static DIJOYSTATE			g_diJoyReleaseState[MAX_JOY];	// �Q�[���p�b�h �����[�X���

// �Q�[���p�b�h�₢���킹�p�R�[���o�b�N�֐�
static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS diDevCaps;
	HRESULT   hr;

	hr = g_pDI->CreateDevice(lpddi->guidInstance, &g_pDIDeviceJoy[g_dwJoystick], NULL);
	if (FAILED(hr)) {
		return DIENUM_CONTINUE;
	}
	diDevCaps.dwSize = sizeof(diDevCaps);
	hr = g_pDIDeviceJoy[g_dwJoystick]->GetCapabilities(&diDevCaps);
	if (FAILED(hr)) {
		SAFE_RELEASE(g_pDIDeviceJoy[g_dwJoystick]);
		return DIENUM_CONTINUE;
	}
	if (++g_dwJoystick < MAX_JOY) return DIENUM_CONTINUE;
	return DIENUM_STOP;
}

// ����������
HRESULT InitDInput(HWND hWnd)
{
	HRESULT hr;
	HINSTANCE hInst;

	hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// DirectInput �I�u�W�F�N�g����
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&g_pDI, NULL);
	if (FAILED(hr)) {
		MessageBoxA(hWnd, "DirectInput�I�u�W�F�N�g�����Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}
	// �L�[�{�[�h �f�o�C�X �I�u�W�F�N�g����
	hr = g_pDI->CreateDevice(GUID_SysKeyboard, &g_pDIDeviceKey, NULL);
	if (FAILED(hr)) {
		SAFE_RELEASE(g_pDI);
		MessageBoxA(hWnd, "�L�[�{�[�h �I�u�W�F�N�g�����Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}
	// �f�[�^ �t�H�[�}�b�g�ݒ�
	hr = g_pDIDeviceKey->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		SAFE_RELEASE(g_pDIDeviceKey);
		SAFE_RELEASE(g_pDI);
		MessageBoxA(hWnd, "�L�[�{�[�h �f�[�^ �t�H�[�}�b�g�ݒ�Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}
	// �������x���̐ݒ�
	hr = g_pDIDeviceKey->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		SAFE_RELEASE(g_pDIDeviceKey);
		SAFE_RELEASE(g_pDI);
		MessageBoxA(hWnd, "�L�[�{�[�h�������x���ݒ�Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}
	// �f�o�C�X�ւ̓��͐���J�n
	hr = g_pDIDeviceKey->Acquire();
	if (FAILED(hr)) {
		SAFE_RELEASE(g_pDIDeviceKey);
		SAFE_RELEASE(g_pDI);
		MessageBoxA(hWnd, "�L�[�{�[�h���͐���J�n�Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}

	// �}�E�X �f�o�C�X �I�u�W�F�N�g����
	hr = g_pDI->CreateDevice(GUID_SysMouse, &g_pDIDeviceMouse, NULL);
	if (FAILED(hr)) {
		SAFE_RELEASE(g_pDIDeviceKey);
		SAFE_RELEASE(g_pDI);
		MessageBoxA(hWnd, "�}�E�X �I�u�W�F�N�g�����Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}
	// �f�[�^ �t�H�[�}�b�g�ݒ�
	hr = g_pDIDeviceMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		SAFE_RELEASE(g_pDIDeviceMouse);
		SAFE_RELEASE(g_pDIDeviceKey);
		SAFE_RELEASE(g_pDI);
		MessageBoxA(hWnd, "�}�E�X �f�[�^ �t�H�[�}�b�g�ݒ�Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}
	// �������x���̐ݒ�
	hr = g_pDIDeviceMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		SAFE_RELEASE(g_pDIDeviceMouse);
		SAFE_RELEASE(g_pDIDeviceKey);
		SAFE_RELEASE(g_pDI);
		MessageBoxA(hWnd, "�}�E�X�������x���ݒ�Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}
	// �f�o�C�X�ݒ�
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;
	g_pDIDeviceMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	// �f�o�C�X�ւ̓��͐���J�n
	hr = g_pDIDeviceMouse->Acquire();
	if (FAILED(hr)) {
		SAFE_RELEASE(g_pDIDeviceMouse);
		SAFE_RELEASE(g_pDIDeviceKey);
		SAFE_RELEASE(g_pDI);
		MessageBoxA(hWnd, "�}�E�X���͐���J�n�Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}
	// �Q�[���p�b�h �f�o�C�X����
	g_dwJoystick = 0;
	hr = g_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)) {
		for (DWORD i = 0; i < g_dwJoystick; ++i)
			SAFE_RELEASE(g_pDIDeviceJoy[i]);
		SAFE_RELEASE(g_pDIDeviceMouse);
		SAFE_RELEASE(g_pDIDeviceKey);
		SAFE_RELEASE(g_pDI);
		MessageBoxA(hWnd, "�Q�[���p�b�h �I�u�W�F�N�g�����Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
		return hr;
	}
	for (DWORD i = 0; i < g_dwJoystick; ++i) {
		// �f�[�^ �t�H�[�}�b�g�ݒ�
		hr = g_pDIDeviceJoy[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)) {
			for (DWORD j = 0; j < g_dwJoystick; ++j)
				SAFE_RELEASE(g_pDIDeviceJoy[j]);
			SAFE_RELEASE(g_pDIDeviceMouse);
			SAFE_RELEASE(g_pDIDeviceKey);
			SAFE_RELEASE(g_pDI);
			MessageBoxA(hWnd, "�Q�[���p�b�h �f�[�^ �t�H�[�}�b�g�ݒ�Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
			return hr;
		}
		// �������x���̐ݒ�
		hr = g_pDIDeviceJoy[i]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(hr)) {
			for (DWORD j = 0; j < g_dwJoystick; ++j)
				SAFE_RELEASE(g_pDIDeviceJoy[j]);
			SAFE_RELEASE(g_pDIDeviceMouse);
			SAFE_RELEASE(g_pDIDeviceKey);
			SAFE_RELEASE(g_pDI);
			MessageBoxA(hWnd, "�Q�[���p�b�h�������x���ݒ�Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
			return hr;
		}
		// �f�o�C�X�ݒ�
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = JOY_MIN_X;
		diprg.lMax = JOY_MAX_X;
		g_pDIDeviceJoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = JOY_MIN_Y;
		diprg.lMax = JOY_MAX_Y;
		g_pDIDeviceJoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// �f�o�C�X�ւ̓��͐���J�n
		hr = g_pDIDeviceJoy[i]->Acquire();
		if (FAILED(hr)) {
			for (DWORD j = 0; j < g_dwJoystick; ++j)
				SAFE_RELEASE(g_pDIDeviceJoy[j]);
			SAFE_RELEASE(g_pDIDeviceMouse);
			SAFE_RELEASE(g_pDIDeviceKey);
			SAFE_RELEASE(g_pDI);
			MessageBoxA(hWnd, "�}�E�X���͐���J�n�Ɏ��s���܂����B", "error", MB_ICONSTOP | MB_OK);
			return hr;
		}
	}

	return hr;
}

// �I������
void UninitDInput()
{
	for (DWORD i = 0; i < g_dwJoystick; ++i) {
		if (g_pDIDeviceJoy[i]) {
			g_pDIDeviceJoy[i]->Unacquire();
		}
		SAFE_RELEASE(g_pDIDeviceJoy[i]);
	}
	if (g_pDIDeviceMouse) {
		g_pDIDeviceMouse->Unacquire();
	}
	SAFE_RELEASE(g_pDIDeviceKey);
	if (g_pDIDeviceKey) {
		g_pDIDeviceKey->Unacquire();
	}
	SAFE_RELEASE(g_pDIDeviceKey);
}

// �X�V����
void UpdateDInput()
{
	HRESULT hr;

	if (g_pDIDeviceKey) {
		g_pDIDeviceKey->Acquire();
		CopyMemory(g_bPrevKeyState, g_bKeyState, 256);
		hr = g_pDIDeviceKey->GetDeviceState(256, g_bKeyState);
		if (hr == DIERR_INPUTLOST)
			g_pDIDeviceKey->Acquire();
		else {
			for (int i = 0; i < 256; ++i) {
				g_bKeyTriggerState[i] = (~g_bPrevKeyState[i] & g_bKeyState[i]) & 0x80;
				g_bKeyReleaseState[i] = (g_bPrevKeyState[i] & ~g_bKeyState[i]) & 0x80;
			}
		}
	}
	if (g_pDIDeviceMouse) {
		g_pDIDeviceMouse->Acquire();
		CopyMemory(&g_diPrevMouseState, &g_diMouseState, sizeof(g_diMouseState));
		hr = g_pDIDeviceMouse->GetDeviceState(sizeof(g_diMouseState), &g_diMouseState);
		if (hr == DIERR_INPUTLOST)
			g_pDIDeviceMouse->Acquire();
		else {
			for (int i = 0; i < 4; ++i) {
				g_diMouseTriggerState.rgbButtons[i] = (~g_diPrevMouseState.rgbButtons[i] & g_diMouseState.rgbButtons[i]) & 0x80;
				g_diMouseReleaseState.rgbButtons[i] = (g_diPrevMouseState.rgbButtons[i] & ~g_diMouseState.rgbButtons[i]) & 0x80;
			}
		}
	}
	for (DWORD i = 0; i < g_dwJoystick; ++i) {
		g_pDIDeviceJoy[i]->Acquire();
		g_pDIDeviceJoy[i]->Poll();
		CopyMemory(&g_diPrevJoyState[i], &g_diJoyState[i], sizeof(g_diJoyState[0]));
		hr = g_pDIDeviceJoy[i]->GetDeviceState(sizeof(g_diJoyState[0]), &g_diJoyState[i]);
		if (hr == DIERR_INPUTLOST)
			g_pDIDeviceJoy[i]->Acquire();
		else {
			for (int j = 0; j < 32; ++j) {
				g_diJoyTriggerState[i].rgbButtons[j] = (~g_diPrevJoyState[i].rgbButtons[j] & g_diJoyState[i].rgbButtons[j]) & 0x80;
				g_diJoyReleaseState[i].rgbButtons[j] = (g_diPrevJoyState[i].rgbButtons[j] & ~g_diJoyState[i].rgbButtons[j]) & 0x80;
			}
		}
	}
}

// �L�[������Ԏ擾
bool DIGetKey(DWORD dwKey)
{
	if (dwKey >= _countof(g_bKeyState)) return false;
	return (g_bKeyState[dwKey] & 0x80) != 0;
}

// �L�[ �g���K��Ԏ擾
bool DIGetKeyTrigger(DWORD dwKey)
{
	if (dwKey >= _countof(g_bKeyTriggerState)) return false;
	return (g_bKeyTriggerState[dwKey] & 0x80) != 0;
}

// �L�[ �����[�X��Ԏ擾
bool DIGetKeyRelease(DWORD dwKey)
{
	if (dwKey >= _countof(g_bKeyReleaseState)) return false;
	return (g_bKeyReleaseState[dwKey] & 0x80) != 0;
}

// �Q�[���p�b�h���擾
DWORD DIGetJoyCount()
{
	return g_dwJoystick;
}

// �Q�[���p�b�h��Ԏ擾
DIJOYSTATE *DIGetJoy(DWORD dwJoy)
{
	if (dwJoy >= g_dwJoystick) return NULL;
	return &g_diJoyState[dwJoy];
}

// �Q�[���p�b�hX���擾
LONG DIGetJoyX(DWORD dwJoy)
{
	if (dwJoy >= g_dwJoystick) return 0;
	return g_diJoyState[dwJoy].lX;
}

// �Q�[���p�b�hY���擾
LONG DIGetJoyY(DWORD dwJoy)
{
	if (dwJoy >= g_dwJoystick) return 0;
	return g_diJoyState[dwJoy].lY;
}

// �Q�[���p�b�hZ���擾
LONG DIGetJoyZ(DWORD dwJoy)
{
	if (dwJoy >= g_dwJoystick) return 0;
	return g_diJoyState[dwJoy].lZ;
}

// �Q�[���p�b�h �{�^��������Ԏ擾
bool DIGetJoyButton(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= g_dwJoystick) return false;
	if (dwBtn >= _countof(g_diJoyState[dwJoy].rgbButtons)) return false;
	return (g_diJoyState[dwJoy].rgbButtons[dwBtn] & 0x80) != 0;
}

// �Q�[���p�b�h �{�^�� �g���K��Ԏ擾
bool DIGetJoyTrigger(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= g_dwJoystick) return false;
	if (dwBtn >= _countof(g_diJoyTriggerState[dwJoy].rgbButtons)) return false;
	return (g_diJoyTriggerState[dwJoy].rgbButtons[dwBtn] & 0x80) != 0;
}

// �Q�[���p�b�h �{�^�� �����[�X��Ԏ擾
bool DIGetJoyRelease(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= g_dwJoystick) return false;
	if (dwBtn >= _countof(g_diJoyReleaseState[dwJoy].rgbButtons)) return false;
	return (g_diJoyReleaseState[dwJoy].rgbButtons[dwBtn] & 0x80) != 0;
}

// �}�E�X��Ԏ擾
DIMOUSESTATE *DIGetMouse()
{
	return &g_diMouseState;
}

// �}�E�X �{�^��������Ԏ擾
bool DIGetMouseButton(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_diMouseState.rgbButtons)) return false;
	return (g_diMouseState.rgbButtons[dwBtn] & 0x80) != 0;
}

// �}�E�X �{�^�� �g���K��Ԏ擾
bool DIGetMouseTrigger(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_diMouseTriggerState.rgbButtons)) return false;
	return (g_diMouseTriggerState.rgbButtons[dwBtn] & 0x80) != 0;
}

// �}�E�X �{�^�� �����[�X��Ԏ擾
bool DIGetMouseRelease(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_diMouseReleaseState.rgbButtons)) return false;
	return (g_diMouseReleaseState.rgbButtons[dwBtn] & 0x80) != 0;
}
