
// ゲームシーンのポーズ画面。
// ステージ選択へ戻れる。
// 
//

#ifndef __PAUSESCREEN__
#define __PAUSESCREEN__

#include"Dxg2d\Font.h"
#include"UIsystem.h"
#include"Dxg2d\GameObj.h"
#include"Move.h"

// ポーズ画面のボタン
enum {
	PAUSE_BUTTON_RESUME,
	PAUSE_BUTTON_RESTART,
	PAUSE_BUTTON_QUIT,
	PAUSE_BUTTON_MAX,

};

class  PauseButton :public  GameObj{
public:
	void Init(int button,float posX,float posY);
	void Update();
	void Draw();

	bool isEnd;			// すべての処理が終わったか
	bool pushed;
private:
	void SwicthButton();

	UIsystem uiSystem;
	bool orvered;
	int buttonNum;
};



class PauseScreen {
public:
	static PauseScreen *Instance() {
		static PauseScreen pauseScreen;
		return &pauseScreen;
	}
	static void Delete() {
		delete Instance();
	}

	PauseScreen() {};
	~PauseScreen() {};

	void Init();
	void Update();
	void Draw();

	bool GetPauseState();

private:

	void BrightChar();

	Move move;
	Font font;
	PauseButton pauseButton[PAUSE_BUTTON_MAX];
	unsigned char alpha;// 点滅用
	float colorNum;		// 点滅用

	bool isPushed;	//
	bool isPause;

};


#endif // !__GAMEMANAGER__
