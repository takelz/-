//=============================================================================
//
// ���C������ [main.cpp]
//
//�`�X�V�����`
//2018/07/24	Dxg2d��ver1.0�����B
//				wii�J���̂��߂ɂ��Ȃ�ׂ�directX�̊֐��ƃR���X�g���N�^�g��Ȃ�
//
//2018/07/31	�R���C�_����̒����B�w��^�O�Ƃ̊ђʂ���	
//
//2018/08/02	�t�b�N�V���b�g�ǉ�
//
//2018/08/04	SpiteAnim��vertex�̌v�Z��ύX
//
//2018/08/17	�X�e�[�W�����v���O�����쐬
//
//2018/09/01	wii�J���I���͏I��
//
//2018/09/04	�t�b�N�V���b�g�͎������Ȃ�
//
//
//
//=============================================================================

#include "main.h"
#include"Dxg2d/input.h"
#include"Dxg2d\sound.h"
#include"Dxg2d/Camera.h"
#include"BackGround.h"

#include"SceneManager.h"
#include"Fade.h"
#include"MagicEmitter.h"
#include"PauseScreen.h"
/*
char str[256];
wsprintf(str, "num:%d\n",i);
MessageBox(NULL, str, "tex", MB_OK);
*/

//*****************************************************************************
// �}�N����`
//***************************************************************************** 	 	


#define CLASS_NAME  	"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME  	"Monochrome Sphere" 	 	// �E�C���h�E�̃L���v�V������
#define FIRST_SCENE (SCENE_TITLE)				// �J�n�V�[��
#define SCREEN_OUT_DIST (1.5f)	 				// ��ʔ͈͊O�̔���������L��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void MainInit(HWND);
void MainDraw();

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
#ifdef _DEBUG
void DrawFPS(void);

#endif

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9  	g_pD3D = NULL; 	// Direct3D �I�u�W�F�N�g
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; 	// Device�I�u�W�F�N�g(�`��ɕK�v)
#ifdef _DEBUG
LPD3DXFONT 	g_pD3DXFont = NULL; 	// �t�H���g�ւ̃|�C���^

int  	g_nCountFPS; 	// FPS�J�E���^
#endif

HWND g_hwnd;			// �E�B���h�E�̏��


//=============================================================================
// ����������
void MainInit(HWND hWnd) {
	HRESULT hr;
	hr = InitDInput(hWnd);

	if (SUCCEEDED(hr)) hr = InitSound(hWnd);
	
	SceneManager::Instance()->ChangeScene(FIRST_SCENE);
	SceneManager::Instance()->SceneTrance();			// �ŏ��̈��ڂ͎蓮�ł�����Ăяo��
	Fade::Instance()->Init();
	Fade::Instance()->StartFadeIn();
	NormalFade::Instance()->StartFadeIn();
	MagicEmitter::Instance()->Init();
	SetVolume(SOUND_BGM_MENU, 0.4f);		// �������ʂ�������
	PlaySound(SOUND_BGM_MENU);		


}


//=============================================================================
// �X�V����
void Update(void) {
	// TODO: �����ɍX�V������ǉ�.
	UpdateDInput();


	Fade::Instance()->Update();
	SceneManager::Instance()->Update();


}

//=============================================================================
// �`�揈��
void MainDraw() {

	SceneManager::Instance()->Draw();
	Fade::Instance()->Draw();
	PauseScreen::Instance()->Draw();
}

//=============================================================================
// �I������
void Uninit(void) {
	UninitDInput();




#ifdef _DEBUG
	if (g_pD3DXFont != NULL) {// ���\���p�t�H���g�̊J��
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
#endif

	if (g_pD3DDevice != NULL) {// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL) {// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}



HWND GetHwnd() {
	return g_hwnd;
}

D3DXVECTOR2 GetMousePos() {
	POINT lpPoint;
	D3DXVECTOR2 mousePos;

	GetCursorPos(&lpPoint);
	ScreenToClient(GetHwnd(), &lpPoint);

	mousePos.x = (float)lpPoint.x;
	mousePos.y = (float)lpPoint.y;

	return mousePos;
}

void SetOnDestBlend() {
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

void SetOffDestBlend() {
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void SetOnBlendOne(){
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE); 			// 
}

void SetOffBlendOne() {
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); 		// ���\�[�X�J���[�̎w��
}



bool IsOutScreen(D3DXVECTOR2 pos) {
	if (pos.x < 0 && SCREEN_WIDTH * SCREEN_OUT_DIST < pos.x && pos.y < 0 && SCREEN_HEIGHT * SCREEN_OUT_DIST < pos.y)
		return true;
	else
		return false;
}




//=============================================================================
// ���C���֐�
//=============================================================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance); // �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);  	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;


	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,0,
		hInstance,NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,CLASS_NAME,NULL
	};

	HWND hWnd;
	MSG msg;

	// COM���C�u����������
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER;	// �E�B���h�E�T�C�Y�Œ�
	DWORD dwExStyle = 0;

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(dwExStyle, CLASS_NAME, WINDOW_NAME,
		dwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics
		(SM_CYCAPTION), NULL, NULL, hInstance, NULL);

	g_hwnd = hWnd;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, TRUE))) {
		return -1;
	}

	//�t���[���J�E���g������
	timeBeginPeriod(1);  	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;


	// ���b�Z�[�W���[�v
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			} else {
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) { // 0.5�b���ƂɎ��s			
			#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
			#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) {
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}

	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// COM���C�u���������
	CoUninitialize();

	// �I������

	Uninit();

	timeEndPeriod(1);  	 	 	// ����\��߂�

	return (int)msg.wParam;
}

// 
static int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs) {
	RECT rcWnd, rcClnt;
	SIZE sizeWnd;

	// �N���C�A���g�̈�T�C�Y���X�N���[���T�C�Y�ɌŒ�
	GetWindowRect(hWnd, &rcWnd);
	GetClientRect(hWnd, &rcClnt);
	sizeWnd.cx = (rcWnd.right - rcWnd.left) - (rcClnt.right - rcClnt.left) + SCREEN_WIDTH;
	sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - (rcClnt.bottom - rcClnt.top) + SCREEN_HEIGHT;
	SetWindowPos(hWnd, NULL, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	// IME�g�p�֎~(�����̑S�p���̓��b�N)
	//ImmAssociateContext(hWnd, NULL);

	return 0;
}


//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
		case WM_CREATE:
			return OnCreate(hWnd, (LPCREATESTRUCT)lParam);
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			switch (wParam) {
				case VK_ESCAPE:
					DestroyWindow(hWnd);
					return 0;
			}
			break;

		default:
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow) {
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));  	// ���[�N���[���N���A 206	d3dpp.BackBufferCount 	= 1; 	// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;  	// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; 	// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;  	// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Đݒ�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow; 	// �E�B���h�E���[�h

	d3dpp.EnableAutoDepthStencil = TRUE; 	// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; 	// �f�v�X�o�b�t�@�Ƃ���16bit��


	if (bWindow) {// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0; 	// ���t���b�V�����[


		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // �C���^�[�o��
	} else

	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; 	// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; 	// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  			// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ���C�e�B���O���Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);  					// Z�o�b�t�@���g�p 259	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);  	// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// �A���t�@���g��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); 		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��B����������
	//g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); 			// ���ꂪ�I�����摜�̉��Z�����ɂȂ�

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT); 	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); 	// �e�N�X�`���g��t�B���^���[�h��ݒ�
	

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); // �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT); // �Q�Ԗڂ̃A���t�@

																			// ���ߐF(�����F)�̕�����Z�o�b�t�@�ɏ������܂Ȃ�
	//g_pd3ddevice->setrenderstate(d3drs_alphatestenable, true);
	//g_pd3ddevice->setrenderstate(d3drs_alpharef, 0);
	//g_pd3ddevice->setrenderstate(d3drs_alphafunc, d3dcmp_greater);


#ifdef _DEBUG
																			// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pD3DXFont);
#endif

	MainInit(hWnd);

	return S_OK;
}

////=============================================================================
//// �I������
////=============================================================================
//void Uninit(void) {
//
//
//
//#ifdef _DEBUG
//	if (g_pD3DXFont != NULL) {// ���\���p�t�H���g�̊J��
//		g_pD3DXFont->Release();
//		g_pD3DXFont = NULL;
//	}
//#endif
//	if (g_pD3DDevice != NULL) {// �f�o�C�X�̊J��
//		g_pD3DDevice->Release();
//		g_pD3DDevice = NULL;
//	}
//
//	if (g_pD3D != NULL) {// Direct3D�I�u�W�F�N�g�̊J��
//		g_pD3D->Release();
//		g_pD3D = NULL;
//	}
//
//}

////=============================================================================
//// �X�V����
////=============================================================================
//void Update(void) {
//	// TODO: �����ɍX�V������ǉ�.
//
//
//
//}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void) {
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene())) {
		// TODO: �����ɕ`�揈����ǉ�

		MainDraw();


	#ifdef _DEBUG
		// FPS�\�� 
		DrawFPS();
	#endif

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================

LPDIRECT3DDEVICE9 GetDevice(void) {
	return g_pD3DDevice;
}

#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void DrawFPS(void) {
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	wsprintf(str, "FPS:%d\n", g_nCountFPS);

	// �e�L�X�g�`��
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif
