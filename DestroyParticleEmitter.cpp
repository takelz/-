


#include"DestroyParticleEmitter.h"

#define GENERATE_CIRCLE_NUM (12)
#define GENERATE_RADIUS (1)
#define SPEED (8.0f)

D3DXVECTOR2 GenerateCirclePos(int count,float posX,float posY) {
	Transform trans;

	float angle = 360.0f / GENERATE_CIRCLE_NUM;
	trans.pos.x = posX + GENERATE_RADIUS * cosf(D3DXToRadian(angle * count));
	trans.pos.y = posY + GENERATE_RADIUS * sinf(D3DXToRadian(angle * count));

	return trans.pos;
}

D3DXVECTOR2 SetupAcc(D3DXVECTOR2 emitTrans,float posX,float posY) {
	D3DXVECTOR2 rtrnMove;

	//rtrnMove.x = cosf(atan2f(emitTrans.pos.y - SCREEN_CENTER_Y, emitTrans.pos.x - SCREEN_CENTER_X));	//ターゲット設定
	//rtrnMove.y = sinf(atan2f(emitTrans.pos.y - SCREEN_CENTER_Y, emitTrans.pos.x - SCREEN_CENTER_X));	//ターゲット設定
	rtrnMove.x = cosf(atan2f(posY - emitTrans.y, posX - emitTrans.x));	//ターゲット設定
	rtrnMove.y = sinf(atan2f(posY - emitTrans.y, posX - emitTrans.x));	//ターゲット設定

	rtrnMove.x *= SPEED;
	rtrnMove.y *= SPEED;


	return rtrnMove;
}

void DestroyParticleEmitter::Init() {
	for (int i = 0; i < MAX_DEST_PARTICLE; i++) {
		destParticle[i].exist = false;
	}

}

void DestroyParticleEmitter::Emission(float posX, float posY) {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 acc;

	// サークル
	for (int generateCount = 1; GENERATE_CIRCLE_NUM >= generateCount; generateCount++) {
		for (int i = 0; i < MAX_DEST_PARTICLE; i++) {
			if (destParticle[i].exist) continue;
			pos = GenerateCirclePos(generateCount,posX,posY);
			acc = SetupAcc(pos, posX, posY);
			destParticle[i].Create(pos.x, pos.y, acc.x, acc.y);
			break;
		}
	}
}


void DestroyParticleEmitter::Update() {
	for (int i = 0; i < MAX_DEST_PARTICLE; i++) {
		if (!destParticle[i].exist)continue;
		destParticle[i].Update();
	}


}


void DestroyParticleEmitter::Draw() {
	for (int i = 0; i < MAX_DEST_PARTICLE; i++) {
		if (!destParticle[i].exist) continue;
		destParticle[i].Draw();
	}

}


