
#include"DestroyParticle.h"

#define FILENAME_DESTEFFECT ("data/texture/perticle02.png")
#define SIZE_X (20)
#define SIZE_Y (20)

#define DISAPPEAR_SPEED (5)

void DestroyParticle::Init() {
	
	if (!loadedSprite) {
		sprite.Load(FILENAME_DESTEFFECT);	
		collision.rigid.Init(&transform);	// コライダ登録せずにrigidを使うのでInitを使う
		loadedSprite = true;
	}
	transform.size.x = SIZE_X;
	transform.size.y = SIZE_Y;
	collision.rigid.useGravity = false;
	sprite.color.r = 255;
	sprite.color.g = 230;
	sprite.color.b = 200;
	sprite.color.a = 255;
}

void DestroyParticle::Create(float posX, float posY, float accX, float accY) {
	Init();	// 初期化

	transform.pos.x = posX;
	transform.pos.y = posY;
	collision.rigid.velocity.x = accX;
	collision.rigid.velocity.y = accY;
	exist = true;
	
}

void DestroyParticle::Update() {

	// 減速
	collision.rigid.velocity.x *= 0.9f;
	collision.rigid.velocity.y *= 0.9f;
	collision.rigid.velocity.y += 0.1f;

	if (0 < sprite.color.a - DISAPPEAR_SPEED ) {	// 消えたら存在を消す
		sprite.color.a -= DISAPPEAR_SPEED;
	} else {
		exist = false;
	}

	collision.rigid.UpdatePos();
	transform.TransformToSprite(&sprite);
	sprite.Update();
}

void DestroyParticle::Draw() {
	sprite.Draw();
}

