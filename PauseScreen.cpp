#include"PauseScreen.h"
#include"Dxg2d\input.h"
#include"Dxg2d\sound.h"
#include"Fade.h"
#include"SceneManager.h"

#define FILE_RESUME "data/texture/UI/resume.png"
#define FILE_RESTART "data/texture/UI/restart.png"
#define FILE_QUIT "data/texture/UI/quit.png"

#define SIZE_X (430*0.4f)
#define SIZE_Y (130*0.4f)

#define BUTTON_POS_Y (250)
#define BUTTON_INTERVAL_POS (100)


void PauseScreen::Init() {
	font.Init();
	isPause = false;
	for (int i = 0; i < PAUSE_BUTTON_MAX; i++) {
		pauseButton[i].Init(i, (float)SCREEN_CENTER_X, BUTTON_POS_Y + i * BUTTON_INTERVAL_POS);
	}

	isPushed = false;
}

void PauseScreen::Update() {
	if (DIGetKeyTrigger(DIK_P)) {
		isPause = !isPause;
	}
	if (isPause) {
		move.ColorBright(&alpha, &colorNum, 4, 100);
		
		NormalFade::Instance()->SetGray(true);
		font.SetAlpha(alpha);
		font.InputChar("PAUSE", SCREEN_CENTER_X - STD_CHAR_SIZE_X/2, SCREEN_CENTER_Y - 200);
		
		for (int i = 0; i < PAUSE_BUTTON_MAX; i++) {
			pauseButton[i].Update();
			if (pauseButton[i].isEnd) isPause = false;			
			if (pauseButton[i].pushed) isPushed = true;		// シーン遷移のボタンを押したら表示を消す
		}
		pauseButton[PAUSE_BUTTON_RESUME].isEnd = false;		// 戻った場合flagをもとに戻す

	} else {
		NormalFade::Instance()->SetGray(false);
	}

}
void PauseScreen::Draw() {
	if (!isPause) return;
	if (isPushed) return;

	font.Draw();

	for (int i = 0; i < PAUSE_BUTTON_MAX; i++) {
		pauseButton[i].Draw();
	}
}

bool PauseScreen::GetPauseState() {
	return isPause;
}

void PauseScreen::BrightChar() {

}

//＝＝＝＝＝PauseButtonクラス＝＝＝＝＝

void PauseButton::Init(int button,float posX,float posY) {
	switch (button) {
		case PAUSE_BUTTON_RESUME:
			sprite.Load(FILE_RESUME);
			break;
		case PAUSE_BUTTON_RESTART:
			sprite.Load(FILE_RESTART);
			break;
		case PAUSE_BUTTON_QUIT:
			sprite.Load(FILE_QUIT);
			break;
	}
	buttonNum = button;
	sprite.pos.x = posX;
	sprite.pos.y = posY;
	sprite.size.x = SIZE_X;
	sprite.size.y = SIZE_Y;
	pushed = false;
	isEnd  = false;
}
void PauseButton::Update() {
	if (uiSystem.Button(sprite.pos, sprite.size)) {
		sprite.color = 128;
		if (!orvered) {
			PlaySound(SOUND_MOUSEOVER);
			orvered = true;
		}

		if (DIGetMouseRelease(DIK_LEFT_CLICK)) {
			SwicthButton();
		}
	} else {
		sprite.color = 255;
		orvered = false;
	}

	if (pushed) {
		if (Fade::Instance()->GetFadeState(true)) {
			isEnd = true;
			if (buttonNum == PAUSE_BUTTON_RESTART) {
				SceneManager::Instance()->Repeat();
			} else {
				SceneManager::Instance()->ChangeScene(SCENE_SELECT);
				NormalFade::Instance()->SetGray(false);			// ポーズ時の灰色の背景をなくす
			}
			Fade::Instance()->StartFadeIn();
		}
	}

	sprite.Update();
}
void PauseButton::Draw() {
	sprite.Draw();
}

void PauseButton::SwicthButton() {
	switch (buttonNum) {
		case PAUSE_BUTTON_RESUME:
			PlaySound(SOUND_ENTER);
			isEnd = true;
			break;
		case PAUSE_BUTTON_RESTART:
			PlaySound(SOUND_ENTER);
			Fade::Instance()->StartFadeOut();
			pushed = true;
			break;
		case PAUSE_BUTTON_QUIT:
			PlaySound(SOUND_ENTER);
			Fade::Instance()->StartFadeOut();
			pushed = true;
			break;
	}
}


