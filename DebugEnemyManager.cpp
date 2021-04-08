
#include"DebugEnemyManager.h"

void DebugEnemyManager::Init() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy[i].exist = false;
	}
}

void DebugEnemyManager::Create(float posX, float posY, float rotat,int num) {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy[i].exist) continue;
		enemy[i].Create(posX, posY, rotat);
		break;
	}
}


void DebugEnemyManager::Update() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].Update();
	}
}

void DebugEnemyManager::EditUpdate() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].EditUpdate();
	}
}


void DebugEnemyManager::Draw() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].exist) continue;
		enemy[i].Draw();
	}

}


