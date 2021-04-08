#include"Fade.h"

//#define FILENAME "data/texture/enemy/enemy00_1.png"
#define FILENAME "data/texture/fade.png"
#define FILENAME_NORMALFADE "data/texture/square.bmp"

#define FADEIN_SPEED	(10)
#define FADEOUT_SPEED	(10)

#define LOADING_POS_X (710)
#define LOADING_POS_Y (600)
#define ACC_SPEED (1.07f)
#define MAX_NUM (3.5f)

#define GRAY_ALPHA (128)

void Fade::Init() {
	sprite.Load(FILENAME);
	sprite.size.x = SCREEN_WIDTH*MAX_NUM;
	sprite.size.y = SCREEN_WIDTH*MAX_NUM;
	sprite.pos.x = 0;
	sprite.pos.y = 0;
	sprite.color.r = sprite.color.g = sprite.color.b = 0;
	sprite.color.a = 255;
	accNum = 1.0f;

	font.Init();
	dispLoading = false;

	NormalFade::Instance()->Init();
}


void Fade::Update() {
	FadeIn();
	FadeOut();
	NormalFade::Instance()->Update();
	font.InputChar("Loading...", LOADING_POS_X, LOADING_POS_Y);
}


void Fade::Draw() {
	sprite.Draw();
	NormalFade::Instance()->Draw();
	if (dispLoading) {
		font.Draw();
	}


}

void Fade::FadeIn() {
	if (!flagIn) return;
	accNum *= ACC_SPEED;

	if (0 < sprite.size.x) {
		sprite.size.x -= FADEIN_SPEED + accNum;
		sprite.size.y -= FADEIN_SPEED + accNum;
		endFadeIn = false;
	} else {
		sprite.size.x = 0;
		sprite.size.y = 0;
		flagIn = false;
		endFadeIn = true;
		accNum = 1.0f;
	}
}

void Fade::FadeOut() {
	if (!flagOut) return;
	accNum *= ACC_SPEED;

	if (SCREEN_WIDTH * MAX_NUM > sprite.size.x) {
		sprite.size.x += FADEOUT_SPEED + accNum;
		sprite.size.y += FADEOUT_SPEED + accNum;
		if (SCREEN_WIDTH * 1.1f < sprite.size.x) {			// 終わる少し前に表示
			dispLoading = true;
		}
	} else {
		sprite.size.x = SCREEN_WIDTH *MAX_NUM;
		sprite.size.y = SCREEN_WIDTH *MAX_NUM;
		flagOut = false;
		endFadeOut = true;
		accNum = 1.0f;

	}
}


void Fade::StartFadeIn() {
	Init();
	dispLoading = false;		// フェードインスタートが呼び出される＝＝ロード終了
	flagIn = true;
	endFadeIn = false;
	sprite.pos.x = 0;
	sprite.pos.y = 0;
}

void Fade::StartFadeOut() {
	
	flagOut = true;
	sprite.pos.x = SCREEN_WIDTH;
	sprite.pos.y = SCREEN_HEIGHT;
	endFadeOut = false;
}


bool Fade::GetFadeState(bool isOut) {
	if (isOut) {
		if (endFadeOut) {
			endFadeOut = false;
			return true;
		}
		return false;
	} else {
		if (endFadeIn) {
			endFadeIn = false;
			return true;
		}

		return false;
	}
}

//＝＝＝＝＝NormalFadeクラス＝＝＝＝＝

void NormalFade::Init() {
	sprite.Load(FILENAME_NORMALFADE);
	sprite.size.x = SCREEN_WIDTH;
	sprite.size.y = SCREEN_WIDTH;
	sprite.pos.x = SCREEN_CENTER_X;
	sprite.pos.y = SCREEN_CENTER_Y;
	sprite.color.r = sprite.color.g = sprite.color.b = 0;
	sprite.color.a = 255;

}


void NormalFade::Update() {
	FadeIn();
	FadeOut();
	ScreenGray();
}


void NormalFade::Draw() {
	sprite.Draw();
}

void NormalFade::FadeIn() {
	if (!flagIn) return;
	if (0 < sprite.color.a - 1) {
		sprite.color.a -= 1;

	} else {
		flagIn = false;
	}
}

void NormalFade::FadeOut() {
	if (!flagOut) return;
	if (sprite.color.a + 1 < 255) {
		sprite.color.a += 1;
	} else {
		flagOut = false;
	}
}

void NormalFade::ScreenGray() {
	if (flagIn || flagOut) return;

	if (flagGray) {
		sprite.color.a = GRAY_ALPHA;
	} else {
		sprite.color.a = 0;
	}
}

void NormalFade::StartFadeIn() {
	if (flagIn) return;
	flagIn = true;
}
void NormalFade::StartFadeOut() {
	if (flagOut) return;
	flagOut = true;
}

bool NormalFade::EndFadeIn() {
	if (sprite.color.a < 5){
		return true;
	} else {
		return false;
	}
}

bool NormalFade::EndFadeOut() {
	if (sprite.color.a > 250){
		return true;
	} else {
		return false;
	}
}



void NormalFade::SetGray(bool isGray) {
	flagGray = isGray;
}

