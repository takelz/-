// 左右にゆらゆら動くパーティクルEmitter
//
//

#ifndef __MAGICEMITTER__
#define __MAGICEMITTER__

#include"main.h"
#include"MagicPerticle.h"
#include"Dxg2d/GameObj.h"

#define MAGIC_MAX (512)

class MagicEmitter{
public:
	static MagicEmitter *Instance() {
		static MagicEmitter magicEmitter;
		return &magicEmitter;
	}
	static void Delete() {
		delete Instance();
	}

	void Init();
	void Update();
	void Draw();


	void Generate();
	void ResetParticle();	// パーティクルのリセット
private:

	D3DXVECTOR2 GenerateCirclePos();
	D3DXVECTOR2 SetupMove(D3DXVECTOR2 emitTrans);
	
	//＝＝＝＝＝変数＝＝＝＝＝
	MagicPerticle magic[MAGIC_MAX];
	int generateCnt;
};

#endif