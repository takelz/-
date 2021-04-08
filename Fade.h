
// StartFadeする場合かならずGetStateのしたに処理を書く
//

#ifndef __FADE__
#define __FADE__

#include"Dxg2d\Sprite.h"
#include"main.h"
#include"Dxg2d\Font.h"

class Fade {
public:
	static Fade *Instance() {
		static Fade fade;
		return &fade;
	}
	static void Delete() {
		delete Instance();
	}

	void Init();
	void Update();
	void Draw();

	void StartFadeOut();// フェードアウト
	//bool EndFadeOut();	// フェードアウトが終わったらtrueを返す
	void StartFadeIn();	// フェードイン
	//bool EndFadeIn();	// フェードインが終わったらtrueを返す

	bool GetFadeState(bool isOut);	// 呼び出したときtrueならfalseに戻す
private:
	void FadeIn();
	void FadeOut();

	Sprite sprite;
	Font font;			// ロード表示
	bool dispLoading;	// フェードアウト終了時にtrueで表示
	bool flagIn;
	bool flagOut;
	bool endFadeOut;	// trueで終わったか
	bool endFadeIn;	// trueで終わったか


	float accNum;	// フェードの加速
};

// 普通の暗くなるフェード
class NormalFade {
public:
	static NormalFade *Instance() {
		static NormalFade normalFade;
		return &normalFade;
	}
	static void Delete() {
		delete Instance();
	}

	void Init();
	void Update();
	void Draw();

	void StartFadeIn();
	void StartFadeOut();
	bool EndFadeIn();
	bool EndFadeOut();

	void SetGray(bool isGray);		// 薄暗い状態にするか

private:
	void FadeIn();
	void FadeOut();
	void ScreenGray();

	bool flagIn;
	bool flagOut;

	bool flagGray;	// 薄暗い状態

	Sprite sprite;
};


#endif // !__FADE__
