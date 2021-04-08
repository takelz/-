
#include"Dxg2d\input.h"
#include"MagicPerticle.h"
#define FILENAME "data/texture/perticle01.png"
#define MAGIC_SIZE (20)
#define END_COUNT (500)
#define START_ADD_VEC_ANGLE (90)
#define EMIT_SPEED (30)
#define END_SPEED (5)
#define SIDE_SPEED (180)
#define SIDE_MAXADD_SPEED (0.01f)
#define RANDOM_SIDE (55)
#define RAND_SIZE_RANGE (35)
#define ADDACC_SPEED (0.09f)


MagicPerticle::MagicPerticle() {
	collision.rigid.Init(&transform);
	transform.notScroll = true;
	exist = false;
}

void MagicPerticle::Emit(D3DXVECTOR2 paramTrans, D3DXVECTOR2 paramVelocity) {
	int randSizeNum = rand() % RAND_SIZE_RANGE;

	transform.pos = paramTrans;
	transform.size.x = MAGIC_SIZE + randSizeNum;
	transform.size.y = MAGIC_SIZE + randSizeNum;
	collision.rigid.velocity = paramVelocity;
	sprite.color.a = 0;
	RandomColor();
	endCnt = 0;
	accPower = 0;
	moveCnt = rand() % RANDOM_SIDE;
	exist = true;
}

void MagicPerticle::RandomColor() {
	const int RAND_COLOR = 60;
	const int COLOR = 255 - RAND_COLOR;

	unsigned char randNum = rand() % RAND_COLOR;
	sprite.color.b = COLOR + randNum;
	sprite.color.r = COLOR + randNum;
	sprite.color.g = COLOR + randNum;
	sprite.color.a = 170;
}

// 左右にゆらゆらゆれる処理
void MagicPerticle::Moving() {
	//sin(PI * 2 / 60 * Count)
	collision.rigid.velocity.x += sinf(3.14f * 2 / SIDE_SPEED * moveCnt) * SIDE_MAXADD_SPEED;
	moveCnt++;
}

// 中心にチャージしていく
void MagicPerticle::MoveCharge() {
	collision.rigid.velocity.x = cosf(atan2f(SCREEN_CENTER_Y - transform.pos.y, SCREEN_CENTER_X - transform.pos.x));	//ターゲット設定
	collision.rigid.velocity.y = sinf(atan2f(SCREEN_CENTER_Y - transform.pos.y, SCREEN_CENTER_X - transform.pos.x));	//ターゲット設定

	collision.rigid.velocity.x += collision.rigid.velocity.x * accPower;
	collision.rigid.velocity.y += collision.rigid.velocity.y * accPower;
	accPower += ADDACC_SPEED;

}

void MagicPerticle::AdjustAlpha() {
	if (END_COUNT < endCnt) {
		if (0 + END_SPEED > sprite.color.a || 0 > transform.pos.y) exist = false;
		else sprite.color.a -= END_SPEED;
	} else {
		endCnt++;

		if (255 - EMIT_SPEED > sprite.color.a)
			sprite.color.a += EMIT_SPEED;
	}

}


void MagicPerticle::Init() {
	sprite.Load(FILENAME);
	transform.size.x = MAGIC_SIZE;
	transform.size.y = MAGIC_SIZE;
	transform.pos.x = SCREEN_CENTER_X;
	transform.pos.y = SCREEN_CENTER_Y;
	exist = false;
}


void MagicPerticle::Update() {

	if (IsOutScreen(transform.pos)) exist = false;	// 画面外にいったら存在を消す

	AdjustAlpha();
	Moving();
	collision.rigid.velocity.x += collision.rigid.velocity.x * 0.002f;
	collision.rigid.velocity.y += collision.rigid.velocity.y * 0.002f;
	accPower = 0.0f;

	collision.rigid.UpdatePos();
	transform.TransformToSprite(&sprite);
	sprite.Update();
}


void MagicPerticle::Draw() {
	sprite.Draw();
}
