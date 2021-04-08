#include"HookShot.h"
#include"PlayerManager.h"
#include"Dxg2d\input.h"


void HookShot::Hook(D3DXVECTOR2 basePos, D3DXVECTOR2 *baseVector) {
	if (!PlayerManager::Instance()->hookOn) {
		rockTrriger = false;
		return;
	} else {
		CheckDirection(basePos, *baseVector);	// ���E�ǂ��炩��̐N����
	}
	if (PlayerManager::Instance()->state != PLAYER_ATACK || DIGetMouseRelease(DIK_RIGHT_CLICK)) {
		PlayerManager::Instance()->hookOn = false;
		return;
	}
	D3DXVECTOR2 vectorAB;	// �|�C���g����v���C���[�ʒu�܂ł̕����x�N�g��
	float baseLength;
	D3DXVECTOR2 direction;	// ����������

	vectorAB = move.VectorDirection(PlayerManager::Instance()->hookPoint, basePos);
	baseLength = sqrtf(baseVector->x * baseVector->x + baseVector->y * baseVector->y);

	direction.x = vectorAB.y;
	direction.y = vectorAB.x;

	// �N����������A�ʒu�ŉ�]�̌��������߂�
	if (enterPosDirX == LEFT) {					// �X�^�[�g�ʒu����
		if (enterOfDirX == RIGHT) {					// �x�N�g�����E��
			if (enterOfDirY == UP) {					// �x�N�g�������
				baseVector->x = direction.x * -baseLength;
				baseVector->y = direction.y * baseLength;
			} else {									// �x�N�g��������
				baseVector->x = direction.x * baseLength;
				baseVector->y = direction.y * -baseLength;
			}
		} else {									// �x�N�g��������
			if (enterOfDirY == UP) {
				baseVector->x = direction.x * baseLength;
				baseVector->y = direction.y * -baseLength;
			} else {
				baseVector->x = direction.x * baseLength;				
				baseVector->y = direction.y * -baseLength;
			}
		}
	} else {									// �X�^�[�g�ʒu���E
		if (enterOfDirX == RIGHT) {
			if (enterOfDirY == UP) {
				baseVector->x = direction.x * baseLength;
				baseVector->y = direction.y * -baseLength;
			} else {
				baseVector->x = direction.x * baseLength;
				baseVector->y = direction.y * -baseLength;
			}
		} else {
			if (enterOfDirY == UP) {
				baseVector->x = direction.x * baseLength;
				baseVector->y = direction.y * -baseLength;
			} else {
				baseVector->x = direction.x * -baseLength;
				baseVector->y = direction.y * baseLength;
			}
		}
	}

}

void HookShot::CheckDirection(D3DXVECTOR2 basePos, D3DXVECTOR2 baseVector) {

	if (rockTrriger) return;
	rockTrriger = true;			// �t�b�N��Ԃ����������܂�false�ɂ͂Ȃ�Ȃ�

	// �����E�ɐi��ł���Ȃ�A�܂荶����̐N���Ȃ�
	if (0 < baseVector.x) {
		enterOfDirX = RIGHT;
	} else {
		enterOfDirX = LEFT;
	}

	if (0 < baseVector.y) {
		enterOfDirY = DOWN;
	} else {
		enterOfDirY = UP;
	}

	if (move.SearchDirectTargetX(PlayerManager::Instance()->hookPoint,basePos)) {
		enterPosDirX = RIGHT;
	} else {
		enterPosDirX = LEFT;
	}



	//if (move.SearchDirectTargetY(basePos, PlayerManager::Instance()->pos)) {
	//	enterPosDirY = 1.0f;
	//} else {
	//	enterPosDirY = -1.0f;
	//}




}