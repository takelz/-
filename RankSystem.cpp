
#include"RankSystem.h"
#include"GameManager.h"
#include"Fade.h"
#include"Dxg2d\sound.h"
#include<stdio.h>

#define FILE_S "data/texture/UI/rank_s.png"
#define FILE_A "data/texture/UI/rank_a.png" 
#define FILE_B "data/texture/UI/rank_b.png"
#define FILE_C "data/texture/UI/rank_c.png"
#define FILE_D "data/texture/UI/rank_d.png"

#define FILE_BACK "data/texture/UI/rankback.png"


#define SCORE_POS_X (380)
#define SCORE_POS_Y (400)
#define SCORE_SIZE_X (STD_CHAR_SIZE_X)
#define SCORE_SIZE_Y (STD_CHAR_SIZE_Y)
#define SCORE_UP_SPEED (10)
#define STOP_TIME (70)

#define RANK_POS_X (SCREEN_CENTER_X + 105)
#define RANK_POS_Y (400)
#define RANK_SIZE_X (150)
#define RANK_SIZE_Y (150)
#define RANK_POP_POS_Y (RANK_POS_Y + 50)	// 出現開始位置

#define BACK_SIZE_X (250)
#define BACK_SIZE_Y (190)
#define BACK_FADE_SPEED (25)




void RankSystem::Init() {
	resultScore = 0;

	GameManager::Instance()->GetRank(&rank);
	rock = true;
	
	font.Init();
	spriteRank[RANK_S].Load(FILE_S);
	spriteRank[RANK_A].Load(FILE_A);
	spriteRank[RANK_B].Load(FILE_B);
	spriteRank[RANK_C].Load(FILE_C);
	spriteRank[RANK_D].Load(FILE_D);
	
	for (int i = 0; i < RANK_MAX; i++) {	// 段々出てくる感じにするので最初見えない
		spriteRank[i].color.a = 0;
		spriteRank[i].pos.y = RANK_POP_POS_Y;

	}
	spriteBack.Load(FILE_BACK);
	spriteBack.size.x = BACK_SIZE_X;
	spriteBack.size.y = BACK_SIZE_Y;
	spriteBack.pos.x = RANK_POS_X + 20;
	spriteBack.pos.y = RANK_POS_Y;
	  
	spriteBack.color.a = 0;
	playedSe = false;
	PlaySound(SOUND_COUNTUP);
}

void RankSystem::Update() {
	if (StopTime(&stopCounter, STOP_TIME)) rock = false;
	
	if(!rock)
		DispScore();

	if (endUp) {
		if (spriteBack.color.a < 255 - BACK_FADE_SPEED) {
			if (200 < spriteRank[resultRank].color.a) {
				if (!playedSe) {
					PlaySound(SOUND_FADEIN);		// 一回だけならす
					playedSe = true;
				}
				spriteBack.color.a += BACK_FADE_SPEED;
			}
		} else {
			if (!pushed) {
				spriteBack.color.a = 255;
			}
		}
	}

	Result();

	PopRank();

	spriteRank[resultRank].size.x = RANK_SIZE_X;
	spriteRank[resultRank].size.y = RANK_SIZE_Y;
	//spriteRank[resultRank].size.y = rankPosY;
	spriteRank[resultRank].pos.x = RANK_POS_X;

	spriteRank[resultRank].Update();
	spriteBack.Update();
}

void RankSystem::Draw() {
	
	spriteBack.Draw();
	spriteRank[resultRank].Draw();

	font.Draw();
}



void RankSystem::Result() {

	if (resultScore >= rank.rank_S) {
		resultRank = RANK_S;
	} else if (resultScore >= rank.rank_A) {
		resultRank = RANK_A;
	} else if (resultScore >= rank.rank_B) {
		resultRank = RANK_B;
	} else if(resultScore >= rank.rank_C){
		resultRank = RANK_C;
	} else {
		resultRank = RANK_D;
	}

}

void RankSystem::PopRank() {
	if (RANK_POS_Y < spriteRank[resultRank].pos.y)
		spriteRank[resultRank].pos.y--;
	else
		spriteRank[resultRank].pos.y = RANK_POS_Y;

	// ボタン押したらフェードアウトするように
	if (pushed) {		
		spriteRank[resultRank].color.a = allAlpha;
		spriteBack.color.a = allAlpha;
		return;
	}

	if (spriteRank[resultRank].color.a < 255 - 2) {
		spriteRank[resultRank].color.a += 2;
	} 

	
}

void RankSystem::DispScore() {
	char numStr[32];

	if (resultScore < GameManager::Instance()->saveScore) {
		resultScore += SCORE_UP_SPEED;
	} else {
		resultScore = GameManager::Instance()->saveScore;
		if (!endUp) {
			StopSound(SOUND_COUNTUP);
			endUp = true;
		}
	}


	wsprintf(numStr, "%d", resultScore);
	font.SetColor(255, 255, 255);
	font.SetAlpha(allAlpha);
	font.InputChar("SCORE:", SCORE_POS_X - SCORE_SIZE_X * 5, SCORE_POS_Y, SCORE_SIZE_X, SCORE_SIZE_Y);

	font.SetAlpha(allAlpha);
	font.InputChar(numStr, SCORE_POS_X, SCORE_POS_Y,SCORE_SIZE_X,SCORE_SIZE_Y);
}

