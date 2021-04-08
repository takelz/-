
#include"EnemyTogeManager.h"

void EnemyTogeManager::Init() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy[i].exist = false;
	}
}

void EnemyTogeManager::Create(float posX, float posY, float rotate,int num) {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy[i].exist) continue;
		enemy[i].Create(posX, posY, rotate,num);
		break;
	}
}


void EnemyTogeManager::Update() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].Update();
	}
}

void EnemyTogeManager::EditUpdate() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].EditUpdate();
	}
}



void EnemyTogeManager::Draw() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].exist) continue;
		enemy[i].Draw();
	}

}


