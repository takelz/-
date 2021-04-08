
#include"UICombo.h"
#include"PlayerManager.h"
#include<string>
#include<stdio.h>

//#define FILE_BACK "data/texture/UI/conboUI.png"
#define BACK_POS_SIZE_X (330)
#define BACK_POS_SIZE_Y (375)
#define SCORE_POS_X (SCREEN_WIDTH - 200)
#define SCORE_POS_Y (125)

#define UP_POINT (100)


void UICombo::Init() {
	font.Init();

	chain = 0;
}


void UICombo::Update() {
	char numStr[128];
	
	chain = PlayerManager::Instance()->GetRushCount();
	sprintf(numStr,"%d",chain);
	if (1 < chain) {
		font.InputChar("chain", SCORE_POS_X , SCORE_POS_Y + 10, STD_CHAR_SIZE_X - 5, STD_CHAR_SIZE_Y - 5);
		font.InputChar(numStr, SCORE_POS_X + 75, SCORE_POS_Y, STD_CHAR_SIZE_X + 25, STD_CHAR_SIZE_Y + 25);
	}
}


void UICombo::Draw() {
	font.SetColor(255, 255, 255);
	font.Draw();
}
