
#include"SceneClear.h"
#include"Dxg2d\input.h"
#include"Dxg2d\sound.h"
#include"SceneManager.h"
#include"GameManager.h"
#include"MagicEmitter.h"


#define FILE_CONTINUE ("data/texture/UI/continue.png")
#define BUTTON_SIZE_X (420 * 0.8f)
#define BUTTON_SIZE_Y (120 * 0.8f)
#define START_BUTTON_POS_X (SCREEN_CENTER_X)
#define START_BUTTON_POS_Y (SCREEN_CENTER_Y + 200)

void SceneClear::Init() {
	//StopSound(SOUND_BGM_GAME);
	bg.Init();
	font.Init();

	rankSystem.Init();

	spriteButton.Load(FILE_CONTINUE);
	spriteButton.pos.x = START_BUTTON_POS_X;
	spriteButton.pos.y = START_BUTTON_POS_Y;
	spriteButton.size.x = BUTTON_SIZE_X;
	spriteButton.size.y = BUTTON_SIZE_Y;
	allAlpha = 255;
	
}

void SceneClear::Update() {
	bg.Update();
	spriteButton.color.a = allAlpha;
	font.SetAlpha(allAlpha);
	font.InputChar("CLEAR", SCREEN_CENTER_X - STD_CHAR_SIZE_X, 200,STD_CHAR_SIZE_X *2,STD_CHAR_SIZE_Y * 2);


	if (uiSystem.Button(spriteButton.pos, spriteButton.size)) {
		spriteButton.color = 128;
		if (!orvered) {
			PlaySound(SOUND_MOUSEOVER);
			orvered = true;
		}
		if (DIGetMouseRelease(DIK_LEFT_CLICK)) {
			//SceneManager::Instance()->ChangeScene(SCENE_SELECT);
			PlaySound(SOUND_ENTER);
			uiSystem.StartFadeOut();
			rankSystem.pushed = true;
		}
	} else {
		orvered = false;
		spriteButton.color = 255;
	}

	if (uiSystem.FadeOutAllUI(&allAlpha)) {
		SceneManager::Instance()->ChangeScene(SCENE_SELECT);
	}

	
	rankSystem.allAlpha = allAlpha;
	rankSystem.Update();
	MagicEmitter::Instance()->Generate();
	MagicEmitter::Instance()->Update();
	spriteButton.Update();
}

void SceneClear::Draw() {
	bg.Draw();
	MagicEmitter::Instance()->Draw();
	font.Draw();
	rankSystem.Draw();
	spriteButton.Draw();

}

void SceneClear::Uninit() {
	delete this;
}