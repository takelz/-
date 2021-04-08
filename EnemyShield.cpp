
#include"EnemyShield.h"
#include"PlayerManager.h"
#define FILENAME "data/texture/enemy/enemy00.png"
#define FILENAME_SHIELD "data/texture/square.bmp"
#define SHIELD_POS (50)
#define SHIELD_SIZE_X (40)
#define SHIELD_SIZE_Y (80)

void EnemyShield::Init() {
	collision.Register(&transform, TAG_ENEMY, C_TYPE_CIRCLE);
	collision.trigger = true;
	collision.SetNotCollideTag(TAG_ENEMY);

	sprite.Load(FILENAME);
	sprite.reverseX = true;
	sprite.color.b = 0;
	transform.size.x = transform.size.y = 40.0f;

	for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
		shieldObj[i].Init();
	}
}

void EnemyShield::Create(float posX, float posY, float rotate,int num) {
	transform.pos.x = posX;
	transform.pos.y = posY;
	transform.rotate = rotate;
	typeNum = num;
	exist = true;
	Init();
}


void EnemyShield::Update() {

	MoveLoop(false,4,2);
	MoveLoop(true,1,3);
	FaceToMove();

	if (collision.OnCollide(TAG_PLAYER)) {
		if (PlayerManager::Instance()->state == PLAYER_ATACK) {	// プレイヤーが攻撃状態なら自身が消える
			exist = false;
			PlayerManager::Instance()->SendRushSuccess();
		}
	}
	
	collision.OnCollide(TAG_GROUND);
	collision.rigid.UpdatePos();
	transform.TransformToSprite(&sprite);
	sprite.Update();

	// シールド
	SetupShield();

	for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
		if (!exist) shieldObj[i].Uninit();
		shieldObj[i].Update();
	}
}

void EnemyShield::EditUpdate() {
	edit.EditObject(&transform, &exist, MANAGER_ENEMYSHIELD, 0);
	transform.TransformToSprite(&sprite);
	sprite.Update();
}



void EnemyShield::Draw() {
	sprite.Draw();

	for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
		shieldObj[i].Draw();
	}
}

void EnemyShield::SetupShield() {
	D3DXVECTOR2 offset;
	offset.x = SHIELD_POS;
	offset.y = 0;
	shieldObj[0].AttachChild(&transform, offset);
	offset.x = -SHIELD_POS;
	shieldObj[1].AttachChild(&transform, offset);

}

//＝＝＝＝＝ShieldObjクラス＝＝＝＝＝


void ShieldObj::Init() {

	collision.Register(&transform, TAG_GROUND, C_TYPE_SQUARE);
	collision.SetNotCollideTag(TAG_GROUND);
	sprite.Load(FILENAME_SHIELD, 0, 1, 1);
	transform.size.x = SHIELD_SIZE_X;
	transform.size.y = SHIELD_SIZE_Y;
	sprite.color.r = sprite.color.g = sprite.color.b = 0;

}

void ShieldObj::Update() {


	collision.rigid.UpdatePos();
	transform.TransformToSprite(&sprite);
	sprite.Update();
}

void ShieldObj::Draw() {
	sprite.Draw();
}

void ShieldObj::Uninit() {
	collision.DeleteCollision();
}

