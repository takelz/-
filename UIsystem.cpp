
#include"UIsystem.h"
#include"Dxg2d\input.h"

#define END_CHANGENUM (5)
#define FADE_SPEED (3)

bool UIsystem::Button(D3DXVECTOR2 pos, D3DXVECTOR2 size) {
	size.x /= 2;
	size.y /= 2;

	if (pos.x - size.x < GetMousePos().x && pos.x + size.x > GetMousePos().x
		&& pos.y - size.y < GetMousePos().y && pos.y + size.y > GetMousePos().y) {
			return true;
	}
	return false;
}

bool UIsystem::FadeOutAllUI(unsigned char *changeNum) {
	if (END_CHANGENUM < *changeNum && isFadeOut) {
		*changeNum += -FADE_SPEED;	
	}
	if (*changeNum <= END_CHANGENUM) {
		isFadeOut = false;
		*changeNum = 0;
		return true;
	}
	return false;
}

void UIsystem::StartFadeOut() {
	isFadeOut = true;
}

bool UIsystem::FadeInAllUI(unsigned char *changeNum) {
	if (*changeNum < 255 - END_CHANGENUM && isFadeIn) {
		*changeNum += FADE_SPEED;
	}
	if (255 + END_CHANGENUM <= *changeNum ) {
		isFadeIn = false;
		*changeNum = 255;
		return true;
	}
	return false;
}

void UIsystem::StartFadeIn() {
	isFadeIn = true;
}


