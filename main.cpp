//=============================================================================
//
// メイン処理 [main.cpp]
//
//～更新履歴～
//2018/07/24	Dxg2dのver1.0完成。
//				wii開発のためにもなるべくdirectXの関数とコンストラクタ使わない
//
//2018/07/31	コライダ周りの調整。指定タグとの貫通を可に	
//
//2018/08/02	フックショット追加
//
//2018/08/04	SpiteAnimのvertexの計算を変更
//
//2018/08/17	ステージ生成プログラム作成
//
//2018/09/01	wii開発終了は終了
//
//2018/09/04	フックショットは実装しない
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
// マクロ定義
//***************************************************************************** 	 	


#define CLASS_NAME  	"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME  	"Monochrome Sphere" 	 	// ウインドウのキャプション名
#define FIRST_SCENE (SCENE_TITLE)				// 開始シーン
#define SCREEN_OUT_DIST (1.5f)	 				// 画面範囲外の判定を少し広く

//*****************************************************************************
// プロトタイプ宣言
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
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9  	g_pD3D = NULL; 	// Direct3D オブジェクト
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; 	// Deviceオブジェクト(描画に必要)
#ifdef _DEBUG
LPD3DXFONT 	g_pD3DXFont = NULL; 	// フォントへのポインタ

int  	g_nCountFPS; 	// FPSカウンタ
#endif

HWND g_hwnd;			// ウィンドウの情報


//=============================================================================
// 初期化処理
void MainInit(HWND hWnd) {
	HRESULT hr;
	hr = InitDInput(hWnd);

	if (SUCCEEDED(hr)) hr = InitSound(hWnd);
	
	SceneManager::Instance()->ChangeScene(FIRST_SCENE);
	SceneManager::Instance()->SceneTrance();			// 最初の一回目は手動でこれを呼び出す
	Fade::Instance()->Init();
	Fade::Instance()->StartFadeIn();
	NormalFade::Instance()->StartFadeIn();
	MagicEmitter::Instance()->Init();
	SetVolume(SOUND_BGM_MENU, 0.4f);		// 少し音量を下げる
	PlaySound(SOUND_BGM_MENU);		


}


//=============================================================================
// 更新処理
void Update(void) {
	// TODO: ここに更新処理を追加.
	UpdateDInput();


	Fade::Instance()->Update();
	SceneManager::Instance()->Update();


}

//=============================================================================
// 描画処理
void MainDraw() {

	SceneManager::Instance()->Draw();
	Fade::Instance()->Draw();
	PauseScreen::Instance()->Draw();
}

//=============================================================================
// 終了処理
void Uninit(void) {
	UninitDInput();




#ifdef _DEBUG
	if (g_pD3DXFont != NULL) {// 情報表示用フォントの開放
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
#endif

	if (g_pD3DDevice != NULL) {// デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL) {// Direct3Dオブジェクトの開放
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
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); 		// αソースカラーの指定
}



bool IsOutScreen(D3DXVECTOR2 pos) {
	if (pos.x < 0 && SCREEN_WIDTH * SCREEN_OUT_DIST < pos.x && pos.y < 0 && SCREEN_HEIGHT * SCREEN_OUT_DIST < pos.y)
		return true;
	else
		return false;
}




//=============================================================================
// メイン関数
//=============================================================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance); // 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);  	// 無くても良いけど、警告が出る（未使用宣言）

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

	// COMライブラリ初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER;	// ウィンドウサイズ固定
	DWORD dwExStyle = 0;

	// ウィンドウの作成
	hWnd = CreateWindowEx(dwExStyle, CLASS_NAME, WINDOW_NAME,
		dwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics
		(SM_CYCAPTION), NULL, NULL, hInstance, NULL);

	g_hwnd = hWnd;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE))) {
		return -1;
	}

	//フレームカウント初期化
	timeBeginPeriod(1);  	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;


	// メッセージループ
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {// PostQuitMessage()が呼ばれたらループ終了
				break;
			} else {
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) { // 0.5秒ごとに実行			
			#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
			#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) {
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}

	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// COMライブラリを閉じる
	CoUninitialize();

	// 終了処理

	Uninit();

	timeEndPeriod(1);  	 	 	// 分解能を戻す

	return (int)msg.wParam;
}

// 
static int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs) {
	RECT rcWnd, rcClnt;
	SIZE sizeWnd;

	// クライアント領域サイズをスクリーンサイズに固定
	GetWindowRect(hWnd, &rcWnd);
	GetClientRect(hWnd, &rcClnt);
	sizeWnd.cx = (rcWnd.right - rcWnd.left) - (rcClnt.right - rcClnt.left) + SCREEN_WIDTH;
	sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - (rcClnt.bottom - rcClnt.top) + SCREEN_HEIGHT;
	SetWindowPos(hWnd, NULL, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	// IME使用禁止(文字の全角入力ロック)
	//ImmAssociateContext(hWnd, NULL);

	return 0;
}


//=============================================================================
// プロシージャ
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
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow) {
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));  	// ワークをゼロクリア 206	d3dpp.BackBufferCount 	= 1; 	// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;  	// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; 	// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;  	// バックバッファフォーマットはディスプレイモードに合わせて設定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow; 	// ウィンドウモード

	d3dpp.EnableAutoDepthStencil = TRUE; 	// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; 	// デプスバッファとして16bitを


	if (bWindow) {// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0; 	// リフレッシュレー


		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // インターバル
	} else

	{// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; 	// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; 	// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  			// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライティングしない
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);  					// Zバッファを使用 259	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);  	// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// アルファを使う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); 		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定。半透明処理
	//g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); 			// これがオン時画像の加算合成になる

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT); 	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); 	// テクスチャ拡大フィルタモードを設定
	

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); // 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT); // ２番目のアルファ

																			// 透過色(抜き色)の部分をZバッファに書き込まない
	//g_pd3ddevice->setrenderstate(d3drs_alphatestenable, true);
	//g_pd3ddevice->setrenderstate(d3drs_alpharef, 0);
	//g_pd3ddevice->setrenderstate(d3drs_alphafunc, d3dcmp_greater);


#ifdef _DEBUG
																			// 情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pD3DXFont);
#endif

	MainInit(hWnd);

	return S_OK;
}

////=============================================================================
//// 終了処理
////=============================================================================
//void Uninit(void) {
//
//
//
//#ifdef _DEBUG
//	if (g_pD3DXFont != NULL) {// 情報表示用フォントの開放
//		g_pD3DXFont->Release();
//		g_pD3DXFont = NULL;
//	}
//#endif
//	if (g_pD3DDevice != NULL) {// デバイスの開放
//		g_pD3DDevice->Release();
//		g_pD3DDevice = NULL;
//	}
//
//	if (g_pD3D != NULL) {// Direct3Dオブジェクトの開放
//		g_pD3D->Release();
//		g_pD3D = NULL;
//	}
//
//}

////=============================================================================
//// 更新処理
////=============================================================================
//void Update(void) {
//	// TODO: ここに更新処理を追加.
//
//
//
//}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void) {
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene())) {
		// TODO: ここに描画処理を追加

		MainDraw();


	#ifdef _DEBUG
		// FPS表示 
		DrawFPS();
	#endif

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


//=============================================================================
// デバイスの取得
//=============================================================================

LPDIRECT3DDEVICE9 GetDevice(void) {
	return g_pD3DDevice;
}

#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void DrawFPS(void) {
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	wsprintf(str, "FPS:%d\n", g_nCountFPS);

	// テキスト描画
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif
