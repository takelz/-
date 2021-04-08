
#include"UIScore.h"
#include"PlayerManager.h"
#include<string>
#include<stdio.h>
#include"GameManager.h"

#define FILE_BACK "data/texture/UI/conboUI.png"
#define BACK_POS_SIZE_X (330)
#define BACK_POS_SIZE_Y (175)
#define SCORE_POS_X (SCREEN_WIDTH - 280)
#define SCORE_POS_Y (50)

#define FADE_SPEED (5)
#define UP_POS (SCORE_POS_X + 55)	//スコアアップの位置
#define UP_START_POS (SCORE_POS_X)	// 
#define MOVE_SPEED (3)
#define UP_POINT (100)
#define RIMIT_UP (500)	// 500以上は上がらない


void UIScore::Init() {
	font.Init();
	spriteBack.Load(FILE_BACK);
	spriteBack.size.x = BACK_POS_SIZE_X;
	spriteBack.size.y = BACK_POS_SIZE_Y;
	spriteBack.pos.x = SCORE_POS_X + 100;
	spriteBack.pos.y = SCORE_POS_Y;

	upNumPos = UP_POS;
	isUpEnd = true;
	score = 0;
}


void UIScore::Update() {
	char numStr[32];
	
	ScoreUp();


	if (upNumAlpha < 255 && !isUpEnd) upNumAlpha+= FADE_SPEED;
	else isUpEnd = true;

	if (upNumPos < UP_POS) {
		upNumPos += MOVE_SPEED;
	} else {
		upNumPos = UP_POS;
		//isUpEnd = true;
	}
	if (FADE_SPEED < upNumAlpha && isUpEnd)upNumAlpha -= 2;		// 消えていく
	//else upNumAlpha = 0;
	
	sprintf(numStr,"%d",score);
	font.SetColor(255, 255, 255);
	font.InputChar(numStr,SCORE_POS_X,SCORE_POS_Y);

	sprintf(numStr, "+%d", upNum);
	font.SetColor(255, 255, 255);
	font.SetAlpha(upNumAlpha);
	font.InputChar(numStr, upNumPos, SCORE_POS_Y + 25 ,STD_CHAR_SIZE_X - 7,STD_CHAR_SIZE_Y - 13);
	spriteBack.Update();
}


void UIScore::Draw() {
	spriteBack.Draw();
	//font.SetColor(255, 255, 255);
	font.Draw();
}
void UIScore::ScoreUp() {
	if (PlayerManager::Instance()->attackSuccess && !upRock) {
		upRock = true;
		upNum = (UP_POINT * PlayerManager::Instance()->GetRushCount()) *0.5f;

		if (RIMIT_UP < upNum) upNum = RIMIT_UP;	// 上限値設定
		
		score += upNum;
		upNumAlpha = 0;
		upNumPos = UP_START_POS;
		isUpEnd = false;

		GameManager::Instance()->saveScore = score;
	}
	if (!PlayerManager::Instance()->attackSuccess) upRock = false;
}