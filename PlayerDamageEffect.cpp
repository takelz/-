
#include"PlayerDamageEffect.h"
#include"PlayerManager.h"
#define FILENAME "data/texture/player/damage.png"
#define FILENAMEEFFECT "data/texture/scr_effect2.png"


void PlayerDamageEffect::Init() {
	sprite.Load(FILENAME);
	sprite.size.x = SCREEN_WIDTH;
	sprite.size.y = SCREEN_HEIGHT;
	sprite.pos.x = SCREEN_CENTER_X;
	sprite.pos.y = SCREEN_CENTER_Y;
	sprite.color.a = 0;
	effect = sprite;
	effect.Load(FILENAMEEFFECT);
	effect.color.a = 255;
	//collision.DeleteCollision();
}


void PlayerDamageEffect::Update() {
	if (PlayerManager::Instance()->enemyAtacked) {
		sprite.color.a = 255;
	}
	if (0 < sprite.color.a) sprite.color.a--;
	sprite.Update();
	effect.Update();
}


void PlayerDamageEffect::Draw() {

	sprite.Draw();
	effect.Draw();
}


