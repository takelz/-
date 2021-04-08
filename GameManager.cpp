#include"GameManager.h"
#include"Fade.h"
#include"SceneManager.h"
#include"Dxg2d\sound.h"

#include"GameManagerScoreSet.h"

void GameManager::GameUpdate() {
	

	if (isGameOver) {
		if (Fade::Instance()->GetFadeState(true)) {
			SceneManager::Instance()->ChangeScene(SCENE_OVER);

			Fade::Instance()->StartFadeIn();
			isGameOver = false;
		}
	}
	if (isGameOver) {		
		Fade::Instance()->StartFadeOut();		
		StopSound();
		PlaySound(SOUND_FADEOUT);
	}
	if (isGameClear) {
		//StopSound();
		//PlaySound(SOUND_FADEOUT);
	}

}

void GameManager::GetRank(RANK *rank) {
	switch (currentStage) {
		case 0:
			*rank = SET_STAGE_1;
			break;
		case 1:
			*rank = SET_STAGE_1;
			break;
		case 2:
			*rank = SET_STAGE_2;
			break;
		case 3:
			*rank = SET_STAGE_3;
			break;
		case 4:
			*rank = SET_STAGE_4;
			break;
		case 5:
			*rank = SET_STAGE_5;
			break;
		case 6:
			*rank = SET_STAGE_6;
			break;

	}
}

