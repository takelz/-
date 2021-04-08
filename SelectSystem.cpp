#include"SelectSystem.h"
#include"Dxg2d\input.h"
#include"Dxg2d\sound.h"
#include"SceneManager.h"
#include"Fade.h"

#define ALINGN_BUTTON_X(RANGE,BUTTONNUM,NUM) ((SCREEN_WIDTH - RANGE) / (BUTTONNUM - 1)) * NUM + RANGE / 2
#define POS_Y (200)
#define FILE_RETURN ("data/texture/UI/return.png")
#define RETURN_POS_X (130)
#define RETURN_POS_Y (600)
#define RETURN_SIZE_X (100)
#define RETURN_SIZE_Y (100)

void SelectSystem::Init() {
	allAplha = 0;


	uiSystem.StartFadeIn();
	font.Init();
	PutButton();
	returnButton.Load(FILE_RETURN);
	returnButton.pos.x = RETURN_POS_X;
	returnButton.pos.y = RETURN_POS_Y;
	returnButton.size.x = RETURN_SIZE_X;
	returnButton.size.y = RETURN_SIZE_Y;

	pushed = false;
}


void SelectSystem::Update() {
	uiSystem.FadeInAllUI(&allAplha);

	font.SetColor(0, 0, 0);
	font.SetAlpha(allAplha);
	font.InputChar("STAGE SELECT", SCREEN_CENTER_X - 10, 70, STD_CHAR_SIZE_X + 5, STD_CHAR_SIZE_Y + 8);

	for (int i = 0; i < MAX_SELECT_BUTTON; i++) {
		if (pushed) continue;				// ‰Ÿ‚³‚ê‚½‚çŠeƒ{ƒ^ƒ“‚ÍŒø‚©‚È‚¢‚æ‚¤‚É
		selectButton[i].alpha = allAplha;
		selectButton[i].Update();
	}

	if (uiSystem.Button(returnButton.pos, returnButton.size)) {
		returnButton.color = 128;
		if (DIGetMouseRelease(DIK_LEFT_CLICK)) {
			PlaySound(SOUND_ENTER);
			Fade::Instance()->StartFadeOut();
			pushed = true;
		}
	} else {
		returnButton.color = 255;
	}

	if (pushed) {
		if (Fade::Instance()->GetFadeState(true)) {
			SceneManager::Instance()->ChangeScene(SCENE_TITLE);
			Fade::Instance()->StartFadeIn();
		}
	}

	returnButton.Update();
	
}


void SelectSystem::Draw() {
	for (int i = 0; i < MAX_SELECT_BUTTON; i++) {
		selectButton[i].Draw();
	}
	returnButton.Draw();
	font.Draw();
}

void SelectSystem::PutButton() {

	float yPos = POS_Y;
	float offsetX = 0;
	float posX;
	int num = 0;
	for (; num < MAX_SELECT_BUTTON; num++) {	// Œ»ó“ñ—ñ
	
		if (num >= 3) {
			yPos = POS_Y * 2;
			offsetX = 3;
		}
		posX = ALINGN_BUTTON_X(400, 3, (num - offsetX));

		selectButton[num].Init(posX, yPos, num + 1);

	}

}
