
#include"EnemyObjToge.h"
#include"PlayerManager.h"

#define FILENAME_TOGETOGE "data/texture/enemy/togetoge01.png"
#define SIZE_X (120-24)
#define SIZE_Y (40-8)

#define BRIGHT_SPEED (4)
#define BRIGHT_RANGE (35)

void EnemyObjToge::Init() {
	collision.Register(&transform, TAG_ENEMY, C_TYPE_SQUARE);
	collision.trigger = true;
	
	sprite.Load(FILENAME_TOGETOGE);
	sprite.color.r = 255;
	sprite.color.g = sprite.color.b = 0;
	transform.size.x = SIZE_X;
	transform.size.y = SIZE_Y;

}


void EnemyObjToge::Create(float posX, float posY, float rotate, int num){
	transform.pos.x = posX;
	transform.pos.y = posY;
	transform.rotate = rotate;
	typeNum = num;
	exist = true;
	Init();
}

void EnemyObjToge::Update(){
	Bright();

	if (collision.OnCollide(TAG_PLAYER)) {
		PlayerManager::Instance()->SetAtackedEnemy();
	}

	transform.TransformToSprite(&sprite);
	sprite.Update();
}

void EnemyObjToge::EditUpdate() {
	edit.EditObject(&transform, &exist, MANAGER_OBJTOGE, 0);
	transform.TransformToSprite(&sprite);
	sprite.Update();
}


void EnemyObjToge::Draw() {
	sprite.Draw();
}

void EnemyObjToge::Bright() {
	move.SignLoop(&brightNum, BRIGHT_SPEED, BRIGHT_RANGE);				// “_–Å
	sprite.color.r = (255 - BRIGHT_RANGE - 1) - (unsigned char)brightNum;
}

