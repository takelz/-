

#include"SpriteAnim.h"
#include"Sprite.h"

void SpriteAnim::Init(int spdCount,int u,int v) {
	timeNextFrame = spdCount;
	spriteU = u;
	spriteV = v;
	curImageX = curImageY = currentU = currentV = 1;	//  バグ防止	
	roopAnim = true;
}

void SpriteAnim::Update(bool anim) {
	// アニメーション更新
	if (anim) {
		if (endAnim)endAnim = false;	// ループフラグをもとにもどす

		if (++frameCount >= timeNextFrame) {
			frameCount = 0;
			curImageX++;  

			if (spriteU < curImageX) {	// 一番右へ行ったら一番左に戻りv軸を一つ追加
				curImageX = 1;
				curImageY++;
			}
			if (spriteV < curImageY) {	// 最後まで行ったら最初に戻る
				if(roopAnim)			// ループを繰り返すなら値をリセット
					curImageX = curImageY = 1;
				endAnim = true;
			}
		}
	} else {
		curImageX = currentU;
		curImageY = currentV;
	}

	for (int i = 0; i < 4; i++) {
		vertexU[i] = (((curImageX - 1) % spriteU) + (i & 1)) * 1.0f / spriteU;		// i&1 iを2で割ったあまり。代入時に両方にマイナス１する。(スタートは0のため)
		vertexV[i] = ((curImageY - 1) + (i >> 1)) * 1.0f / spriteV;
	}

}

bool SpriteAnim::GetEndAnim() {
	return endAnim;
}

