#include"HookShot.h"
#include"PlayerManager.h"
#include"Dxg2d\input.h"


void HookShot::Hook(D3DXVECTOR2 basePos, D3DXVECTOR2 *baseVector) {
	if (!PlayerManager::Instance()->hookOn) {
		rockTrriger = false;
		return;
	} else {
		CheckDirection(basePos, *baseVector);	// 左右どちらからの侵入か
	}
	if (PlayerManager::Instance()->state != PLAYER_ATACK || DIGetMouseRelease(DIK_RIGHT_CLICK)) {
		PlayerManager::Instance()->hookOn = false;
		return;
	}
	D3DXVECTOR2 vectorAB;	// ポイントからプレイヤー位置までの方向ベクトル
	float baseLength;
	D3DXVECTOR2 direction;	// 向かう方向

	vectorAB = move.VectorDirection(PlayerManager::Instance()->hookPoint, basePos);
	baseLength = sqrtf(baseVector->x * baseVector->x + baseVector->y * baseVector->y);

	direction.x = vectorAB.y;
	direction.y = vectorAB.x;

	// 侵入する方向、位置で回転の向きを決める
	if (enterPosDirX == LEFT) {					// スタート位置が左
		if (enterOfDirX == RIGHT) {					// ベクトルが右へ
			if (enterOfDirY == UP) {					// ベクトルが上へ
				baseVector->x = direction.x * -baseLength;
				baseVector->y = direction.y * baseLength;
			} else {									// ベクトルが下へ
				baseVector->x = direction.x * baseLength;
				baseVector->y = direction.y * -baseLength;
			}
		} else {									// ベクトルが左へ
			if (enterOfDirY == UP) {
				baseVector->x = direction.x * baseLength;
				baseVector->y = direction.y * -baseLength;
			} else {
				baseVector->x = direction.x * baseLength;				
				baseVector->y = direction.y * -baseLength;
			}
		}
	} else {									// スタート位置が右
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
	rockTrriger = true;			// フック状態が解除されるまでfalseにはならない

	// もし右に進んでいるなら、つまり左からの侵入なら
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