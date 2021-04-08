#include"SelectButton.h"
#include"SceneManager.h"
#include"Dxg2d\input.h"
#include"Dxg2d\sound.h"
#include"Fade.h"
#include"GameManager.h"

#define FILE_1 "data/texture/UI/_stage1.png"
#define FILE_2 "data/texture/UI/_stage2.png"
#define FILE_3 "data/texture/UI/_stage3.png"
#define FILE_4 "data/texture/UI/_stage4.png"
#define FILE_5 "data/texture/UI/_stage5.png"
#define FILE_6 "data/texture/UI/_stage6.png"

#define SIZE_X (240 * 0.7f)
#define SIZE_Y (130 * 0.7f)



void SelectButton::Init(float posX,float posY,int number) {
	stageNumber = number;

	switch (stageNumber) {
		case 0:
			sprite.Load(FILE_1);
			break;
		case 1:
			sprite.Load(FILE_1);
			break;
		case 2:
			sprite.Load(FILE_2);
			break;
		case 3:
			sprite.Load(FILE_3);
			break;
		case 4:
			sprite.Load(FILE_4);
			break;
		case 5:
			sprite.Load(FILE_5);
			break;
		case 6:
			sprite.Load(FILE_6);
			break;
	}
	
	sprite.size.x = SIZE_X;
	sprite.size.y = SIZE_Y;
	sprite.pos.x = posX;
	sprite.pos.y = posY;
	


}

void SelectButton::Update() {

	if (uiSystem.Button(sprite.pos, sprite.size)) {
		sprite.color = 128;
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
		sprite.color = 255;
		overed = false;
	}

	if (pushed) {
		if (Fade::Instance()->GetFadeState(true)) {

			SceneManager::Instance()->stageNum = (StageNum)stageNumber;
			GameManager::Instance()->currentStage = stageNumber;


			SceneManager::Instance()->ChangeScene(SCENE_GAME);
			Fade::Instance()->StartFadeIn();
		}
	}
	sprite.color.a = alpha;
	sprite.Update();
}


void SelectButton::Draw() {
	sprite.Draw();
}


