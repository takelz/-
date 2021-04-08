// typenum
// .0 静止
// .1 左右移動
// .2 上下移動
// .3 回転移動
//
#include"EnemyNormal.h"
#include"PlayerManager.h"
#include"DestroyParticleEmitter.h"
#include"Dxg2d\Camera.h"
#include"Dxg2d\sound.h"

#define FILENAME "data/texture/enemy/enemy00_1.png"	// 光る本体

#define FILENAME_EFECT "data/texture/enemy/LightEfect.png"

#define SIZE (60/2)

#define MOVE_SPEED (1)
#define MOVE_RANGE (2.2f)

#define BRIGHT_SPPED (2)
#define BRIGHT_RANGE (30)


void EnemyNormal::Init() {
	collision.Register(&transform, TAG_ENEMY, C_TYPE_CIRCLE);
	collision.trigger = false;
	collision.SetNotCollideTag(TAG_ENEMY);
	//collision.rigid.useGravity = true;
	sprite.Load(FILENAME);
	sprite.color.r = 255;
	sprite.color.g = 200;
	sprite.color.b = 100;

	transform.size.x = transform.size.y = SIZE;

	enemyEffect.Init(SIZE*1.3f, SIZE*1.3f);

}

void EnemyNormal::Create(float posX, float posY, float rotate,int num) {
	transform.pos.x = posX;
	transform.pos.y = posY;
	transform.rotate = rotate;
	exist = true;
	Init();

}



void EnemyNormal::Update() {

	SelectMove();

	FaceToMove();

	if (collision.OnCollide(TAG_PLAYER)) {
		if (PlayerManager::Instance()->state == PLAYER_ATACK) {	// プレイヤーが攻撃状態なら自身が消える
			exist = false;
			PlayerManager::Instance()->SendRushSuccess();
			Camera::Instance()->Shake();
			DestroyParticleEmitter::Instance()->Emission(transform.pos.x, transform.pos.y);	// エフェクト
			PlaySound(SOUND_DESTORY);
		}
	}

	collision.OnCollide(TAG_GROUND);
	collision.rigid.UpdatePos();
	transform.TransformToSprite(&sprite);
	sprite.Update();

	enemyEffect.AttachChild(&transform);
	enemyEffect.Update();
}


void EnemyNormal::EditUpdate() {
	edit.EditObject(&transform, &exist, MANAGER_ENEMYNORMAL, typeNum);
	transform.TransformToSprite(&sprite);
	sprite.Update();
	enemyEffect.AttachChild(&transform);
	enemyEffect.Update();
}


void EnemyNormal::Draw() {
	sprite.Draw();

	enemyEffect.Draw();
}

void EnemyNormal::MoveToPlayer() {
	collision.rigid.velocity = move.VectorDirection(transform.pos, PlayerManager::Instance()->pos);
}

void EnemyNormal::FaceToMove() {
	if (0 < collision.rigid.velocity.x) {
		sprite.reverseX = false;
	} else {
		sprite.reverseX = true;
	}
}

void EnemyNormal::MoveLoop(bool isSide,float speed,float range) {
	if (isSide) {
		move.SignLoop(&collision.rigid.velocity.x, (int)speed, range);
	} else {
		move.SignLoopB(&collision.rigid.velocity.y, (int)speed, range);
	}

}

void EnemyNormal::SelectMove() {
	switch (typeNum) {
		case 0:
			break;
		case 1:			// 左右
			MoveLoop(true, MOVE_SPEED, MOVE_RANGE);
			break;
		case 2:			// 上下
			MoveLoop(false, MOVE_SPEED, MOVE_RANGE);
			break;
		case 3:			// 回転
			MoveLoop(true, MOVE_SPEED, MOVE_RANGE);
			MoveLoop(false, MOVE_SPEED, MOVE_RANGE);
			break;

	}

}



//＝＝＝＝＝光るエフェクト＝＝＝＝＝


void EnemyNormalEffect::Init(float sizeX,float sizeY) {
	sprite.Load(FILENAME_EFECT);
	sprite.color.r = 255;
	sprite.color.g = 170;
	sprite.color.b = 0;
	transform.size.x = sizeX;
	transform.size.y = sizeY;
}

void EnemyNormalEffect::Update() {
	move.SignLoop(&colorNum, BRIGHT_SPPED, BRIGHT_RANGE);
	sprite.color.a = (255 - BRIGHT_RANGE - 1) - (unsigned char)colorNum;
	transform.TransformToSprite(&sprite);
	sprite.Update();

	sprite.size *= 1.1f;
}

void EnemyNormalEffect::Draw() {
	SetOnDestBlend();

	sprite.Draw();
	SetOffDestBlend();
}
