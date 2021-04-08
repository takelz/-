
#include"BackGround.h"
#define FILENAME "data/texture/background.png"

void BackGround::Init() {
	sprite.Load(FILENAME);
	sprite.size.x = SCREEN_WIDTH;
	sprite.size.y = SCREEN_HEIGHT;
	sprite.pos.x = SCREEN_CENTER_X;
	sprite.pos.y = SCREEN_CENTER_Y;
	sprite.color.r = sprite.color.g = sprite.color.b = 255;
	//collision.DeleteCollision();

	//magicEmitter.Init();
}


void BackGround::Update() {
	sprite.Update();
	//magicEmitter.Generate();
	//magicEmitter.Update();
}


void BackGround::Draw() {
	sprite.Draw();
	//magicEmitter.Draw();
}


