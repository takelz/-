
#include"UILife.h"
#include"PlayerManager.h"

#define FILENAME_LIFE ("data/texture/circle1.png")
#define SIZE_X (35)
#define SIZE_Y (35)
#define OFFSET_POS (45)
#define POS_X (0)
#define POS_Y (50)

#define BRIGHT_SPEED (4)
#define BRIGHT_RANGE (80)

#define WARNING_LIFENUM (1)

void UILife::Init() {
	sprite.Load(FILENAME_LIFE);
	sprite.size.x = SIZE_X;
	sprite.size.y = SIZE_Y;

}


void UILife::Update() {
	playerHP = PlayerManager::Instance()->playerHP;

	// “®‚«
	sprite.pos.x = POS_X;
	sprite.pos.y = POS_Y;
	if (WARNING_LIFENUM >= playerHP) {
		move.SignLoop(&moveNum, 3, 1);	// ­‚µ“®‚©‚·
	} else {
		move.SignLoop(&moveNum, 2, 0.5f);	// ­‚µ“®‚©‚·
	}
	sprite.pos.y += moveNum;

	// F
	if (WARNING_LIFENUM >= playerHP) {
		move.ColorBright(&rgb, &colorNum, BRIGHT_SPEED*3, BRIGHT_RANGE);
	} else {
		move.ColorBright(&rgb, &colorNum, BRIGHT_SPEED, BRIGHT_RANGE);
	}
	sprite.color.r = sprite.color.g = sprite.color.b = rgb;



	sprite.Update();
}


void UILife::Draw() {
	for (int i = 0; i < playerHP; i++) {	// HP‚Ì”•ª•\Ž¦
		sprite.pos.x += OFFSET_POS;
		sprite.Draw();
	}
}

