// 0	動かないトゲ
// 1	縦に動くトゲ
// 2	破壊できないトゲ、常にトゲ
// 3	縦に動く、破壊できない常にトゲ
// 4	
//
//
#include"EnemyToge.h"
#include"PlayerManager.h"
#include"DestroyParticleEmitter.h"
#include"Dxg2d\Camera.h"
#include"Dxg2d\sound.h"

#define FILENAME_CLOSS "data/texture/enemy/enemy00_2.png"	// ×
#define FILENAME_MAIN "data/texture/enemy/enemy00_1.png"	// 光る本体
#define FILENAME_TOGE "data/texture/enemy/enemy00_toge.png"

#define FILENAME_EFECT "data/texture/enemy/LightEfect.png"

#define ENEMY_TOGE_SIZE (60/2)

#define TOGE_ROTATE_SPEED (5)
#define TOGE_BRIGHT_SPEED (3)
#define TOGE_BRIGHT_RANGE (52)

#define MOVE_SPEED (4.0f)
#define MOVE_RANGE (7.0f)
#define NOT_MOVE_SPEED (1.0f)
#define NOT_MOVE_RANGE (0.1f)

// typenumによって動きがかわる
enum {		
	NOT_MOVE = 0,
	MOVE_VERTICAL,
	NOT_DESTROY,
	NOT_DESTORY_MOVE,
};

void EnemyToge::Init() {
	collision.Register(&transform, TAG_ENEMY, C_TYPE_CIRCLE);
	collision.trigger = true;
	collision.SetNotCollideTag(TAG_ENEMY);

	sprite.Load(FILENAME_MAIN);
	sprite.color.r = 255;
	sprite.color.g = 170;
	sprite.color.b = 0;
	
	transform.size.x = transform.size.y = ENEMY_TOGE_SIZE;



	// ×のスプライト
	spriteCloss.Load(FILENAME_CLOSS);
	spriteCloss.color.r = spriteCloss.color.g = spriteCloss.color.b = 0;
	spriteCloss.color.a = 64;

	spriteEffect.Load(FILENAME_EFECT);
	spriteEffect.color.r = 255;
	spriteEffect.color.g = 170;
	spriteEffect.color.b = 0;

	if (typeNum == NOT_DESTROY || typeNum == NOT_DESTORY_MOVE) {
		sprite.color.r = sprite.color.g = sprite.color.b = 0;	// 破壊できないなら真っ黒に
		spriteEffect.color.r = spriteEffect.color.g = spriteEffect.color.b = 80;
	}

	togeObj.Init();
}

void EnemyToge::Create(float posX, float posY, float rotate,int num) {
	transform.pos.x = posX;
	transform.pos.y = posY;
	transform.rotate = rotate;
	typeNum = num;
	exist = true;
	Init();
}


void EnemyToge::Update() {

	if (typeNum == NOT_MOVE || typeNum == NOT_DESTROY) {		
		MoveLoop(false, NOT_MOVE_SPEED, NOT_MOVE_RANGE);
	} else {
		MoveLoop(false, MOVE_SPEED, MOVE_RANGE);
	}
	FaceToMove();


	if (collision.OnCollide(TAG_PLAYER)) {
		if (typeNum != NOT_DESTROY)		// 破壊不能でないなら
			if (PlayerManager::Instance()->state == PLAYER_ATACK && !togeObj.isToge) {	// プレイヤーが攻撃状態なら自身が消える
				exist = false;
				PlayerManager::Instance()->SendRushSuccess();
				Camera::Instance()->Shake();
				DestroyParticleEmitter::Instance()->Emission(transform.pos.x, transform.pos.y);
				PlaySound(SOUND_DESTORY);
			}
	}

	if (typeNum == NOT_DESTROY || typeNum == NOT_DESTORY_MOVE) {
		togeObj.isToge = true;
	} else {
		if (PlayerManager::Instance()->GetRushCount() % 2) {
			togeObj.isToge = true;
		} else {
			togeObj.isToge = false;
		}
	}


	collision.OnCollide(TAG_GROUND);
	collision.rigid.UpdatePos();
	transform.TransformToSprite(&sprite);
	transform.TransformToSprite(&spriteCloss);
	transform.TransformToSprite(&spriteEffect);
	sprite.Update();
	spriteCloss.Update();
	spriteEffect.Update();

	// トゲ
	SetupToge();

	togeObj.Update();
	spriteEffect.size *= 1.3f;
}

void EnemyToge::EditUpdate() {
	edit.EditObject(&transform, &exist, MANAGER_ENEMYTOGE, typeNum);
	transform.TransformToSprite(&sprite);
	sprite.Update();
	spriteCloss.Update();
}



void EnemyToge::Draw() {

	togeObj.Draw();
	sprite.Draw();	

	SetOnDestBlend();

	spriteEffect.Draw();
	SetOffDestBlend();
	spriteCloss.Draw();

}

void EnemyToge::SetupToge() {
	togeObj.AttachChild(&transform, 0.0f,0.0f);

}

//＝＝＝＝＝TogeObjクラス＝＝＝＝＝


void TogeObj::Init() {
	collision.Register(&transform, TAG_ENEMY, C_TYPE_CIRCLE);
	collision.trigger = true;
	sprite.Load(FILENAME_TOGE);
	transform.size.x = ENEMY_TOGE_SIZE * 2.1f;
	transform.size.y = ENEMY_TOGE_SIZE * 2.1f;
	sprite.color.g = sprite.color.b = 0;
}

void TogeObj::Update() {
	static float num;

	move.SignLoop(&num, TOGE_BRIGHT_SPEED, TOGE_BRIGHT_RANGE);				// 点滅
	sprite.color.r = (255 - TOGE_BRIGHT_RANGE - 1) - (unsigned char)num;	
	transform.rotate += TOGE_ROTATE_SPEED;

	if (isToge) {											// 回数によってニュっと出てきたり引っ込んだり
		if (transform.size.x <= ENEMY_TOGE_SIZE * 2.1f) {
			transform.size.x += 10;
			transform.size.y += 10;
		} else {
			transform.size.x = ENEMY_TOGE_SIZE * 2.1f;
			transform.size.y = ENEMY_TOGE_SIZE * 2.1f;
		}
	} else {
		if (transform.size.x >= ENEMY_TOGE_SIZE / 2 - 10) {
			transform.size.x -= 10;
			transform.size.y -= 10;
		} else {
			
		}
	}


	if (collision.OnCollide(TAG_PLAYER) && isToge) {
		PlayerManager::Instance()->SetAtackedEnemy();
	}

	collision.rigid.UpdatePos();
	transform.TransformToSprite(&sprite);
	sprite.Update();
}

void TogeObj::Draw() {
	sprite.Draw();
}

void TogeObj::Uninit() {
	collision.DeleteCollision();
}

