
#include"SceneOver.h"
#include"Dxg2d\input.h"
#include"Dxg2d\sound.h"
#include"SceneManager.h"
#include"Fade.h"

#define FILE_CONTINUE ("data/texture/UI/continue.png")
#define BUTTON_SIZE_X (420 * 0.8f)
#define BUTTON_SIZE_Y (120 * 0.8f)
#define START_BUTTON_POS_X (SCREEN_CENTER_X)
#define START_BUTTON_POS_Y (SCREEN_CENTER_Y + 200)


void SceneOver::Init() {
	StopSound(SOUND_BGM_GAME);
	bg.Init();
	font.Init();
	damageffect.Init();

	spriteButton.Load(FILE_CONTINUE);
	spriteButton.pos.x = START_BUTTON_POS_X;
	spriteButton.pos.y = START_BUTTON_POS_Y;
	spriteButton.size.x = BUTTON_SIZE_X;
	spriteButton.size.y = BUTTON_SIZE_Y;

}

void SceneOver::Update() {
	bg.Update();
	damageffect.Update();
	move.ColorBright(&color, &colorNum, 4, 100);
	font.SetColor(color, color/2, color/2);
	font.InputChar("GAME OVER", SCREEN_CENTER_X - 17, SCREEN_CENTER_Y, STD_CHAR_SIZE_X * 1.5f, STD_CHAR_SIZE_Y * 1.5f);
	//font.InputChar("PUSH SPASE", SCREEN_CENTER_X, SCREEN_CENTER_Y + 100, STD_CHAR_SIZE_X, STD_CHAR_SIZE_Y);

	if (pushed) {
		if (Fade::Instance()->GetFadeState(true)) {
			SceneManager::Instance()->ChangeScene(SCENE_TITLE);
			Fade::Instance()->StartFadeIn();
			PlaySound(SOUND_BGM_MENU);
		}
	}

	if (uiSystem.Button(spriteButton.pos, spriteButton.size)) {
		spriteButton.color = 128;
		if (!overed) {
			PlaySound(SOUND_MOUSEOVER);
			overed = true;
		}
		if (DIGetMouseRelease(DIK_LEFT_CLICK)) {
			Fade::Instance()->StartFadeOut();
			PlaySound(SOUND_ENTER);
			PlaySound(SOUND_FADEOUT);
			pushed = true;
		}

	} else {
		overed = false;
		spriteButton.color = 255;
	}

}

void SceneOver::Draw() {
	bg.Draw();
	font.Draw();
	damageffect.Draw();
	spriteButton.Draw();
}

void SceneOver::Uninit() {
	delete this;
}