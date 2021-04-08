
#include"Dxg2d\Transform.h"
#include"Dxg2d\input.h"
#include"MagicEmitter.h"
#define MAGIC_SIZE (25)
#define POS_RANDRANGE (SCREEN_WIDTH * 3)
#define MOVE_RANDRANGE (10)
#define GENERATE_CIRCLE_NUM (8)
#define GENERATE_RADIUS (200)
#define INTERVAL_GENERATE (3)

void MagicEmitter::Generate() {
	D3DXVECTOR2 emitTrans;
	D3DXVECTOR2 emitVelocity;

	//
	generateCnt++;
	if (INTERVAL_GENERATE > generateCnt) return;
	for (int i = 0; i < MAGIC_MAX; i++) {
		if (magic[i].exist) continue;
		emitTrans = GenerateCirclePos();
		emitVelocity = SetupMove(emitTrans);
		magic[i].Emit(emitTrans,emitVelocity);
		break;
	}

}

void MagicEmitter::ResetParticle() {
	for (int i = 0; i < MAGIC_MAX; i++) {
		magic[i].exist = false;
	}
}

D3DXVECTOR2 MagicEmitter::GenerateCirclePos() {
	Transform trans;

	//float angle = 360.0f / GENERATE_CIRCLE_NUM;
	//trans.pos.x = SCREEN_CENTER_X + GENERATE_RADIUS * cosf(D3DXToRadian(angle * count));
	//trans.pos.y = SCREEN_CENTER_Y + GENERATE_RADIUS * sinf(D3DXToRadian(angle * count));
	trans.pos.x = (float)SCREEN_CENTER_X + rand() % POS_RANDRANGE - POS_RANDRANGE/2;
	trans.pos.y = (float)SCREEN_CENTER_Y + 400;

	//POINT lpPoint;

	//GetCursorPos(&lpPoint);
	//ScreenToClient(GetHwnd(),&lpPoint);

	//trans.pos.x = lpPoint.x;
	//trans.pos.y = lpPoint.y;
	
	return trans.pos;
}

D3DXVECTOR2 MagicEmitter::SetupMove(D3DXVECTOR2 emitTrans) {
	D3DXVECTOR2 rtrnMove;
	
	rtrnMove.x = 0;
	rtrnMove.y = -1.0f - (rand() % 20) / 10;

	return rtrnMove;
}

void MagicEmitter::Init() {
	for (int i = 0; i < MAGIC_MAX; i++) {
		magic[i].Init();
	}
	generateCnt = 0;
}

void MagicEmitter::Update() {
	if (DIGetKey(DIK_Z)) {
		Generate();
	}

	for (int i = 0; i < MAGIC_MAX; i++) {
		if (!magic[i].exist) continue;
		magic[i].Update();
	}


}


void MagicEmitter::Draw() {

	for (int i = 0; i < MAGIC_MAX; i++) {
		if (!magic[i].exist) continue;
		magic[i].Draw();
	}
}

