
#include"SceneTitle.h"
#include"Dxg2d\input.h"
#include"Dxg2d\sound.h"
#include"SceneManager.h"
#include"Fade.h"

#define FILE_START_BUTTON ("data/texture/UI/startbutton.png")
#define FILE_TITLENAME "data/texture/titlename.png"
#define BUTTON_SIZE_X (420 * 0.8f)
#define BUTTON_SIZE_Y (120 * 0.8f)
#define START_BUTTON_POS_X (SCREEN_CENTER_X)
#define START_BUTTON_POS_Y (SCREEN_CENTER_Y + 200)



void SceneTitle::Init() {
	bg.Init();
	

	titleSystem.Init();



	Fade::Instance()->StartFadeIn();
}

void SceneTitle::Update() {
	bg.Update();
	MagicEmitter::Instance()->Generate();
	MagicEmitter::Instance()->Update();
	titleSystem.Update();

	
}

void SceneTitle::Draw() {
	bg.Draw();
	MagicEmitter::Instance()->Draw();
	titleSystem.Draw();

}

void SceneTitle::Uninit() {
	delete this;
}

//TitleSystemƒNƒ‰ƒX

void TitleSystem::Init() {
	font.Init();
	titleName.Load(FILE_TITLENAME);
	titleName.pos.x = SCREEN_CENTER_X;
	titleName.pos.y = SCREEN_CENTER_Y - 100;
	titleName.size.x = 750;
	titleName.size.y = 245;

	startButton.Load(FILE_START_BUTTON);
	startButton.size.x = BUTTON_SIZE_X;
	startButton.size.y = BUTTON_SIZE_Y;
	startButton.pos.x = START_BUTTON_POS_X;
	startButton.pos.y = START_BUTTON_POS_Y;

	allAlpha = 255;

}

void TitleSystem::Update() {


	if (uiSystem.Button(startButton.pos, startButton.size)) {
		startButton.color.r = startButton.color.g = startButton.color.b = 128;
		if (!overed) {
			PlaySound(SOUND_MOUSEOVER);
			overed = true;
		}
		if (DIGetMouseRelease(DIK_LEFT_CLICK)) {
			uiSystem.StartFadeOut();
			PlaySound(SOUND_ENTER);
		}
	} else {
		startButton.color.r = startButton.color.g = startButton.color.b = 255;
		overed = false;
	}

	if (uiSystem.FadeOutAllUI(&allAlpha)) {
			SceneManager::Instance()->ChangeScene(SCENE_SELECT);
	}
	
	startButton.color.a = titleName.color.a = allAlpha;
	font.SetAlpha(allAlpha);

	titleName.Update();
	font.InputChar("Monochrome Sphere", SCREEN_CENTER_X-5, SCREEN_CENTER_Y - 200,STD_CHAR_SIZE_X * 0.8f,STD_CHAR_SIZE_Y*0.8f);
	startButton.Update();
	 
}

void TitleSystem::Draw() {
	startButton.Draw();
	titleName.Draw();
	font.Draw();
}

