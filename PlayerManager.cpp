
#include"PlayerManager.h"
#include"Dxg2d\Camera.h"

void PlayerManager::SetAtackedEnemy() {
	D3DXVECTOR2 knockBack;
	knockBack.x = 0.0f;
	knockBack.y = 0.0f;

	SetAtackedEnemy(knockBack);
}

void PlayerManager::SetAtackedEnemy(D3DXVECTOR2 paramKnockBack) {
	enemyAtacked = true;
	knockBack = paramKnockBack;
}

bool PlayerManager::GetAttackedState(D3DXVECTOR2 *paramKnockBack) {
	if (enemyAtacked){			
		*paramKnockBack = knockBack;
		enemyAtacked = false;
		return true;
	}
	paramKnockBack->x = 0.0f;
	paramKnockBack->y = 0.0f;

	return false;
}

bool PlayerManager::GetAttackedState() {
	D3DXVECTOR2 damy;
	damy.x = damy.y = 0;
	return GetAttackedState(&damy);

}

int PlayerManager::GetRushCount() {
	return rushCount;
}

void PlayerManager::CountUpRush() {
	rushCount++;
}

void PlayerManager::ResetRushCount() {
	rushCount = 0;
}

void PlayerManager::SendRushSuccess() {
	CountUpRush();
	attackSuccess = true;
}

void PlayerManager::StartHook(D3DXVECTOR2 position) {
	hookOn = true;
	hookPoint = position;
}

D3DXVECTOR2 PlayerManager::GetStartPos() {
	D3DXVECTOR2 returnNum;
	returnNum.x = startPos.x - Camera::Instance()->pos.x;
	returnNum.y = startPos.y - Camera::Instance()->pos.y;

	return returnNum;
}

