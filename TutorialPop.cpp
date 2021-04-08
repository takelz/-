// このオブジェクトはspriteとtransformを切り離して扱う
//
#include"TutorialPop.h"
#include"PlayerManager.h"

#define FILE_POP_MOVE	"data/texture/UI/pop_move.png"
#define FILE_POP_ATTACK	"data/texture/UI/pop_attack.png"
#define FILE_POP_ATTACKSTOP	"data/texture/UI/pop_attackstop.png"
#define FILE_POP_GAGE	"data/texture/UI/pop_gage.png"
#define FILE_POP_HP		"data/texture/UI/pop_hp.png"
#define FILE_POP_CHAIN	"data/texture/UI/pop_score.png"

#define FILE_COLLIDER "data/texture/square.bmp"

#define POP_POS_X (SCREEN_CENTER_X)
#define POP_POS_Y (105)

#define POP_SIZE_X (600)
#define POP_SIZE_Y (65)

#define COLL_SIZE_X (600)
#define COLL_SIZE_Y (350)


void TutorialPop::Init() {
	switch (objNum) {
		case TUTO_POP_MOVE:
			sprite.Load(FILE_POP_MOVE);
			break;
		case TUTO_POP_ATTACK:
			sprite.Load(FILE_POP_ATTACK);
			secondSprite.Load(FILE_POP_ATTACKSTOP);
			break;
		case TUTO_POP_GAGE:
			sprite.Load(FILE_POP_GAGE);
			break;
		case TUTO_POP_HP:
			sprite.Load(FILE_POP_HP);
			break;
		case TUTO_POP_CHAIN:
			sprite.Load(FILE_POP_CHAIN);
			break;			
	}
	sprite.pos.x = POP_POS_X;
	sprite.pos.y = POP_POS_Y;

	sprite.size.x = POP_SIZE_X;
	sprite.size.y = POP_SIZE_Y;

	transform.size.x = POP_SIZE_X;
	transform.size.y = POP_SIZE_Y;

	sprite.color.a = 0;
	
	dispPop = false;
}

void TutorialPop::Create(float posX, float posY, int paramObjNUm) {
	transform.pos.x = posX;
	transform.pos.y = posY;

	objNum = paramObjNUm;
	exist = true;
	Init();
}

void TutorialPop::Update() {
	if (move.DistancePosition(transform.pos, PlayerManager::Instance()->pos, COLL_SIZE_Y)) {
		if (sprite.color.a < 200 - 3) {
			sprite.color.a += 3;
		}
	} else {
		if (0 + 3 < sprite.color.a ) {
			sprite.color.a -= 3;
		} else {
			sprite.color.a = 0;
		}
	}
	sprite.Update();
	if (objNum == TUTO_POP_ATTACK) {
		secondSprite.pos = sprite.pos;
		secondSprite.size = sprite.size;
		secondSprite.color.a = sprite.color.a;
		secondSprite.pos.y = POP_POS_Y + POP_SIZE_Y - 10;
		secondSprite.Update();
	}
}

void TutorialPop::EditUpdate() {		// エディットでは判定がわかりやすくする用に
	edit.EditObject(&transform, &exist, MANAGER_POP, objNum);

	if (!editLoeaded) {
		sprite.Load(FILE_COLLIDER);
		sprite.color.a = 128;
		sprite.color.r = sprite.color.b = 55;
		transform.size.x = COLL_SIZE_X;
		transform.size.y = COLL_SIZE_Y;
		editLoeaded = true;
	}
	transform.TransformToSprite(&sprite);
	sprite.Update();

}

void TutorialPop::Draw() {
	
	sprite.Draw();
	if (objNum == TUTO_POP_ATTACK) {

		secondSprite.Draw();
	}

}

