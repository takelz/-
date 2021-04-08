
#include"DebugEnemy.h"
#include"PlayerManager.h"
#define FILENAME "data/texture/testchara.png"

void DebugEnemy::Init() {
	collision.Register(&transform, TAG_ENEMY, C_TYPE_CIRCLE);
	collision.trigger = false;
	collision.rigid.useGravity = true;
	//collision.SetNotCollideTag(TAG_ENEMY);
	sprite.Load(FILENAME);
	sprite.reverseX = true;
	transform.size.x = transform.size.y = 40.0f;

}

void DebugEnemy::Create(float posX, float posY, float rotate) {
	transform.pos.x = posX;
	transform.pos.y = posY;
	transform.rotate = rotate;
	exist = true;
	Init();
}



void DebugEnemy::Update() {
	if (move.SearchDirectTargetX(transform.pos, PlayerManager::Instance()->pos)) {
	//	sprite.reverseX = false;
	//	collision.rigid.vector.x += 1;
	//} else {
	//	sprite.reverseX = true;
	//	collision.rigid.vector.x -= 1;
	}
	collision.rigid.velocity = move.VectorDirection(transform.pos, PlayerManager::Instance()->pos);

	if (collision.OnCollide(TAG_PLAYER)) {
		if (PlayerManager::Instance()->state == PLAYER_ATACK) {	// ƒvƒŒƒCƒ„[‚ªUŒ‚ó‘Ô‚È‚ç
			exist = false;
			PlayerManager::Instance()->SendRushSuccess();	// UŒ‚‚ª¬Œ÷‚µ‚½‚Æ’m‚ç‚¹‚é
		} else if(PlayerManager::Instance()->state == PLAYER_NORMAL){
			D3DXVECTOR2 knockBack;
			PlayerManager::Instance()->SetAtackedEnemy();
		}
	}

	collision.OnCollide(TAG_GROUND);
	collision.rigid.UpdatePos();
	transform.TransformToSprite(&sprite);
	sprite.Update();
}

void DebugEnemy::EditUpdate() {
	edit.EditObject(&transform, &exist, MANAGER_DEBUGENEMY,0);
	transform.TransformToSprite(&sprite);
	sprite.Update();
}


void DebugEnemy::Draw() {
	sprite.Draw();
}


