

#include"SpriteAnim.h"
#include"Sprite.h"

void SpriteAnim::Init(int spdCount,int u,int v) {
	timeNextFrame = spdCount;
	spriteU = u;
	spriteV = v;
	curImageX = curImageY = currentU = currentV = 1;	//  �o�O�h�~	
	roopAnim = true;
}

void SpriteAnim::Update(bool anim) {
	// �A�j���[�V�����X�V
	if (anim) {
		if (endAnim)endAnim = false;	// ���[�v�t���O�����Ƃɂ��ǂ�

		if (++frameCount >= timeNextFrame) {
			frameCount = 0;
			curImageX++;  

			if (spriteU < curImageX) {	// ��ԉE�֍s�������ԍ��ɖ߂�v������ǉ�
				curImageX = 1;
				curImageY++;
			}
			if (spriteV < curImageY) {	// �Ō�܂ōs������ŏ��ɖ߂�
				if(roopAnim)			// ���[�v���J��Ԃ��Ȃ�l�����Z�b�g
					curImageX = curImageY = 1;
				endAnim = true;
			}
		}
	} else {
		curImageX = currentU;
		curImageY = currentV;
	}

	for (int i = 0; i < 4; i++) {
		vertexU[i] = (((curImageX - 1) % spriteU) + (i & 1)) * 1.0f / spriteU;		// i&1 i��2�Ŋ��������܂�B������ɗ����Ƀ}�C�i�X�P����B(�X�^�[�g��0�̂���)
		vertexV[i] = ((curImageY - 1) + (i >> 1)) * 1.0f / spriteV;
	}

}

bool SpriteAnim::GetEndAnim() {
	return endAnim;
}

